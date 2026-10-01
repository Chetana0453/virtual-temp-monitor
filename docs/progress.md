# Virtual Temperature Sensor Monitoring System using a Linux Device Driver and C++

## Project Progress

## Objective
Develop a software-based temperature monitoring system using a Linux device driver and a C++ application. Temperature readings will be simulated, so no physical sensor is required.

## Progress — 1 October 2026
- Set up Ubuntu on WSL2.
- Running kernel: 6.6.87.2-microsoft-standard-WSL2.
- Prepared the kernel build files for compiling external modules.
- Compiled a test module named hello.ko.
- Successfully loaded and unloaded the module.
- Verified the startup and cleanup messages in the kernel log.
- Created a local Git repository and committed the test module.

## Issue Observed
A BTF debug-information mismatch warning appeared during loading. The test module still loaded and unloaded successfully. Sensor functionality has not been implemented or tested yet.

## Next Step
Implement a virtual temperature sensor device that supports reading and updating a simulated temperature, then connect it to a C++ application.
