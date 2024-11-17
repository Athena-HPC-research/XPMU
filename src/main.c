#include <stdio.h>
#include <ctype.h>
#include "RAPL.h"

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 3)
	{
        printf("Invalid amount of arguments\n");
        printf("[file]: OPTIONAL, specifies the file the output should be stored at\n");
        printf("[minutes]: OPTIONAL, specifies the amount of time the program should run in minutes\n");
        exit(-1);
    }

    if (argc == 1)
	{
        TerminalMode();
    }
	else
	{
        if (isdigit(*argv[2]) == 0)
		{
            printf("The [minutes] argument must be a number\n");
            exit(-1);
        }

        DaemonMode(argv[1], atoi(argv[2]));
    }

	return 0;
}