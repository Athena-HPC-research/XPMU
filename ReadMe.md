# XPMU
XPMU (x86 Power Measurement Utility) is a tool meant for measuring and tracking the power usage of x86 based processors.

It has the following modes:
1) Terminal
2) Background

Terminal mode is meant for debugging, it will constantly display watts being used by the processor with a 4 digit accuracy.

Example
```sh
sudo ./xpmu
```

Background mode is meant for prolonged measurements for measuring the power usage for benchmarking purposes. It requires two parameters, the name of the output file and the length of time to run. The background mode runs as a daemon.

The following example demonstrates how to run the XPMU program for 120 minutes. This example will output 120 files (so that the memory usage stays as low as possible) named file0 all the way to file119. Each file records a single minute of CPU power draw with 60 measurements, each one represents a second.

Example
```sh
sudo ./xpmu file 120
```
