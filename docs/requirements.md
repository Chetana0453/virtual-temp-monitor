# Project Requirements Document

## 1. Project Title
Virtual Temperature Sensor Monitoring System using a Linux Device Driver and C++

## 2. Objective
Develop a software-based temperature sensor using a Linux device driver
written in C and a user-space monitoring application written in C++.

The project demonstrates device-file operations, system calls, input
validation, synchronization, and communication between user space
and kernel space without requiring physical sensor hardware.

## 3. Problem Statement
Learning device-driver development often requires access to hardware.
A virtual sensor provides a way to practise and test device communication
without a physical sensor.

The driver stores a simulated temperature that a user can update.
The C++ application reads and displays this value. The project does
not measure the actual temperature of the computer or its surroundings.

## 4. Project Scope

### Included
- A Linux kernel module written in C.
- A misc character device exposed as /dev/vtemp.
- Reading and updating a simulated temperature.
- Validation of temperature updates.
- Mutex protection for the shared temperature value.
- A C++ command-line application that reads the device.
- Manual testing, documentation, and Git version control.

### Outside the Current Scope
- Physical temperature sensors.
- A graphical interface or mobile application.
- Network communication and cloud storage.
- Persistent temperature storage across module reloads.
- Continuous monitoring or automatic temperature generation.

## 5. Development Environment
- Operating system: Ubuntu on WSL2.
- Kernel version used: 6.6.87.2-microsoft-standard-WSL2.
- Driver language: C.
- Application language: C++17.
- Tools: GCC, G++, Make, Git, and Nano.
- A compatible kernel build tree with the required build artifacts.
- Administrator privileges for loading and unloading the module
  and accessing the device with its current permissions.

## 6. Functional Requirements

### FR-01: Device Registration
Loading the driver shall register a misc character device accessible
through /dev/vtemp.

### FR-02: Initial Temperature
The driver shall initialize the temperature to 25 degrees Celsius
each time the module is loaded.

### FR-03: Temperature Reading
Reading /dev/vtemp shall return the stored temperature as decimal
text followed by a newline.

After the complete value has been read, subsequent reads using the
same file position shall return end-of-file.

### FR-04: Temperature Updates
Writing a valid decimal integer to /dev/vtemp shall update the
stored temperature.

### FR-05: Accepted Range
The driver shall accept integer temperatures from -40 to 125 degrees
Celsius, including both limits.

### FR-06: Invalid Input Handling
The driver shall reject malformed input, oversized input, and
temperatures outside the accepted range.

A rejected update shall leave the previous temperature unchanged.
A zero-byte write shall leave the temperature unchanged.

### FR-07: Shared Data Protection
The driver shall use a mutex to protect access to the shared
temperature value during reading and updating.

### FR-08: C++ Monitoring Application
The C++ application shall open /dev/vtemp, read the temperature,
close the device, and display the reading in degrees Celsius.

The current application shall display one reading per execution.

### FR-09: Application Error Reporting
The application shall report an error and return a nonzero exit
status when it cannot open, read, or interpret the device data.

### FR-10: Device Removal
Unloading the driver shall deregister the device and remove
/dev/vtemp.

## 7. Non-Functional Requirements

### NFR-01: Language and Platform
Project implementation shall use C and C++ and run on Linux.

### NFR-02: Resource Management
The application shall close opened file descriptors.
The driver shall deregister its device during module removal.

### NFR-03: Access Control
The device shall use permissions 0600, restricting read and write
access to the device owner, normally root.

### NFR-04: Code Quality
The code shall use meaningful names and clear module boundaries.
Application builds shall enable compiler warnings.

### NFR-05: Reproducibility
The README shall document prerequisites and commands for building,
loading, running, testing, and unloading the project.

A compatible kernel build environment is required to reproduce
the driver build.

### NFR-06: Version Control
Source code and documentation shall be maintained using Git
and uploaded to GitHub. Generated build files shall be ignored.

### NFR-07: Test Evidence
Test documentation shall record inputs, expected results, actual
results, and pass/fail status. Tests not yet executed shall be
marked as pending.

## 8. System Modules

### 8.1 Linux Device Driver
File: driver/vtemp.c

Responsibilities:
- Register and deregister /dev/vtemp.
- Store the simulated temperature.
- Handle device read and write operations.
- Validate updates.
- Protect the shared value using a mutex.

### 8.2 C++ Monitoring Application
File: app/monitor.cpp

Responsibilities:
- Access the device using Linux system calls.
- Read and interpret the temperature.
- Display the result.
- Report errors.

### 8.3 Build Support
File: driver/Makefile

Responsibilities:
- Define the kernel modules to build.
- Work with the external Linux kernel build system.

The C++ application is compiled using the documented G++ command.

### 8.4 Documentation
Location: README.md and docs/

Responsibilities:
- Explain requirements and design.
- Provide execution instructions.
- Record progress, tests, limitations, and results.

## 9. Acceptance Criteria
The project shall be considered ready for demonstration when:

1. The driver and C++ application build successfully in the
   documented environment.
2. Loading the driver creates /dev/vtemp.
3. The initial reading is 25 degrees Celsius.
4. A valid update is reflected in both a device read and the
   C++ application's output.
5. Boundary values -40 and 125 are accepted.
6. Out-of-range values -41 and 126 are rejected without changing
   the stored temperature.
7. Malformed and oversized input is rejected without changing
   the stored temperature.
8. The application reports an error when the device is unavailable.
9. Unloading the module removes the device.
10. Reloading the module resets the temperature to 25.
11. Concurrent read/write testing produces only valid readings
    and no observed kernel errors.
12. Source code, documentation, diagrams, and recorded test
    results are available on GitHub.

## 10. Development Plan and Timeline
This document was prepared on 2 October 2026 after the initial
prototype was implemented. The schedule below distinguishes
completed work from planned work.

### Completed Through 1 October
- Set up Ubuntu on WSL2 and the kernel build environment.
- Compile, load, and unload a test module.
- Implement the virtual temperature device.
- Implement the C++ reading application.
- Perform basic valid and invalid temperature tests.
- Upload the prototype and README to GitHub.

### 2 October — Requirements and Design
- Document project requirements and scope.
- Prepare architecture and UML diagrams.
- Update progress notes.

### 3 October — Testing and Corrections
- Test boundaries, malformed input, and oversized writes.
- Test application errors and module reload behaviour.
- Test concurrent access.
- Record results and fix identified defects.

### 4 October — Final Documentation and Rehearsal
- Complete the project report and test documentation.
- Check the README against the final implementation.
- Prepare and rehearse a 5–10 minute demonstration.
- Upload final changes and arrange trainer evaluation.

### 5 October — Submission Deadline
- Confirm that all required deliverables are on GitHub.
- Submit the repository link through the required channel.
- Attend evaluation at the time agreed with the trainer.

## 11. Deliverables
- Linux device-driver source code in C.
- Monitoring application source code in C++.
- Driver Makefile and build instructions.
- Project Requirements Document.
- System architecture diagram.
- UML class, sequence, and state-machine diagrams.
- Test cases and recorded results.
- Progress documentation and final project report.
- GitHub repository and working demonstration.

## 12. Constraints and Risks
- The sensor is simulated and does not use physical hardware.
- Kernel modules require a compatible kernel build environment.
- Loading the driver and accessing the device require suitable
  privileges.
- The stored value is lost when the module is unloaded.
- A BTF warning was observed during earlier module loading;
  loading and basic operations succeeded in those tests.
- Additional features are secondary to completing testing,
  documentation, and the required demonstration.

## 13. Possible Future Improvements
- Update temperatures directly from the C++ application.
- Add periodic monitoring and temperature alerts.
- Record readings with timestamps.
- Introduce automated tests written in C or C++.
- Adapt the design for a physical temperature sensor.
