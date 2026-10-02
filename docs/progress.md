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


## Update — 2 October 2026

### Work Completed
- Added the project requirements and development plan.
- Added system architecture, class, sequence, and state diagrams.
- Checked that the diagrams display correctly on GitHub.
- Completed ten manual tests covering temperature limits,
  invalid input, application errors, module reload, permissions,
  and basic concurrent access.
- Recorded test results in docs/testing.md.

### Results and Observations
- Valid temperatures were accepted.
- Invalid updates preserved the previous temperature.
- The application reported missing-device and permission errors.
- Reloading the driver reset the temperature to 25 C.
- Twenty readings during concurrent updates returned 30 C or 40 C,
  with no visible application or write errors.
- The reviewed kernel-log excerpt contained BTF warnings but
  no visible vtemp crash or stack trace.

### Documentation Note
The requirements and design documents were prepared after
the initial working prototype.

### Next Steps
- Update the README to reflect the completed tests.
- Complete the final project report.
- Review the code and practise explaining each component.
- Prepare the 5–10 minute demonstration and arrange evaluation.
