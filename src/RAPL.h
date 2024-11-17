#ifndef raplh
#define raplh

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "buffer.h"

#define MAXIMUM_CORES 256
#define MAXIMUM_PACKAGES 2

typedef struct CPU_Information
{
	int cores;
	int packages;
} CPU_Information;

/// @brief Gets the information of the CPU like how many packages there are and cores
/// @return The CPU_Information struct containing the package / core information
CPU_Information GetCpuInformation();

/// @brief Gets the power consumption of the CPU via the RAPL registers
/// @param packages The total CPUs of the system
/// @param filenames The filenames the RAPL values are located at
/// @return The power consumption of the packages
long long ReadPackagePowerConsumption(int packages, char filenames[MAXIMUM_PACKAGES][64]);

/// @brief Just a wrapper for the ReadPackagePowerConsumption function
/// @param cores The total cores of the system
/// @param packages The total packages of the system
/// @return The power consumption of the system
double ReadRapl(int cores, int packages);

/// @brief The terminal mode of the XPMU
void TerminalMode();

/// @brief The daemon mode of the XPMU, generates a snapshot of the consumption every minute the daemon mode runs
/// @param filename The snapshot file to be created with all the readings
/// @param minutes_to_run The minutes to run in daemon mode
void DaemonMode(char* filename, int minutes_to_run);

#endif