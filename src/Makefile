SHELL:=/bin/bash

COMPILER=gcc
OUTPUT=xpmu

debug:
	$(COMPILER) buffer.c RAPL.c main.c -o $(OUTPUT)

optimised:
	$(COMPILER) buffer.c RAPL.c main.c -O3 -o $(OUTPUT)

clean:
	rm xpmu