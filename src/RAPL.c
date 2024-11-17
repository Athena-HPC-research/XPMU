#include "RAPL.h"

CPU_Information GetCpuInformation()
{
	CPU_Information cpu_information;
	char filename[64];
	FILE* cpuFile;
	int previous_package = -1;
	int current_package = 0;

	cpu_information.cores = 0;
	cpu_information.packages = 0;

	for (int i = 0; i < MAXIMUM_CORES; i++)
	{
		sprintf(filename, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id", i);
		cpuFile = fopen(filename, "r");
		
		if (cpuFile == NULL)
		{
			break;
		}

		fscanf(cpuFile, "%d", &current_package);
		fclose(cpuFile);

		if (previous_package != current_package)
		{
			previous_package = current_package;
			cpu_information.packages++;
		}

		cpu_information.cores++;
	}

	return cpu_information;
}

long long ReadPackagePowerConsumption(int packages, char filenames[MAXIMUM_PACKAGES][64])
{
	FILE* power_consumption_file;
	long long package_power_consumption;

	for (int i = 0; i < packages; i++)
	{
		power_consumption_file = fopen(filenames[i],"r");
			
        if (power_consumption_file == NULL)
        {
            printf("Error opening %s\n", filenames[i]);
        }
        else
        {
            fscanf(power_consumption_file, "%lld", &package_power_consumption);
            fclose(power_consumption_file);
        }
	}

	return package_power_consumption;
}

double ReadRapl(int cores, int packages)
{
	char filenames[MAXIMUM_PACKAGES][64];
	long long before;
	long long after;

	for (int i = 0; i < packages; i++)
	{
		sprintf(filenames[i], "/sys/class/powercap/intel-rapl/intel-rapl:%d/energy_uj", i);
	}

	before = ReadPackagePowerConsumption(packages, filenames);
	sleep(1);
	after = ReadPackagePowerConsumption(packages, filenames);

	return ((double) after - (double) before) / 1000000;
}

void TerminalMode() {
	CPU_Information cpu_information = GetCpuInformation();

	while (1)
	{
        printf("%.4lf W\n", ReadRapl(cpu_information.cores, cpu_information.packages));
    }
}

void DaemonMode(char* filename, int minutes_to_run) {
	CPU_Information cpu_information = GetCpuInformation();
    char* filenameBuffer = CreateBuffer(200);
    char* filenameCounterBuffer = CreateBuffer(200);
    int filenameCounter = 0;

    sprintf(filenameCounterBuffer, "%d", filenameCounter);
    strcpy(filenameBuffer, filename);
    strcat(filenameBuffer, filenameCounterBuffer);

    // We want to run this in the background only in file mode, terminal mode is meant for testing
    daemon(1, 1);

    for (int i = 0; i < minutes_to_run; i++)
	{
        FILE* output_file = fopen(filenameBuffer, "w");

        filenameCounter++;

        sprintf(filenameCounterBuffer, "%d", filenameCounter);
        strcpy(filenameBuffer, filename);
        strcat(filenameBuffer, filenameCounterBuffer);

        for (int i = 0; i < 60; i++)
		{
            fprintf(output_file, "%li %.4lf\n", time(NULL), ReadRapl(cpu_information.cores, cpu_information.packages));
        }

        fclose(output_file);
    }
}