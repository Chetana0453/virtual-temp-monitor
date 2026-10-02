# Project Report

## 1. Project Title
Virtual Temperature Sensor Monitoring System using a Linux Device Driver and C++

## 2. Introduction
This project demonstrates communication between a C++ application
and a Linux device driver.

The driver stores a simulated temperature in kernel memory.
The application reads it through the device file /dev/vtemp
and displays the result.

No physical sensor is connected. The value is set manually
and does not represent the laptop's actual temperature.

## 3. Problem and Objective
Physical hardware is not always available for learning driver
development. A virtual device provides a practical way to explore
device operations without a sensor.

The objective is to implement and test:
- A Linux character-device interface.
- Temperature reading and validated updates.
- A C++ application using Linux system calls.
- Mutex protection of shared data.
- Error handling and documented testing.

## 4. Tools and Environment
- Ubuntu on WSL2.
- Kernel: 6.6.87.2-microsoft-standard-WSL2.
- C for the kernel driver.
- C++17 for the monitoring application.
- GCC, G++, Make, Git, and Nano.
- A compatible kernel build environment.

## 5. System Design
The system has two main components:

### Linux Driver
The driver registers /dev/vtemp and stores an integer temperature.
It handles read and write requests and validates temperature updates.

### C++ Application
The TemperatureMonitor class opens the device, reads its value,
closes the device, and returns the temperature for display.

The application runs in user space. The driver runs in kernel space.
Linux routes device operations to the driver's callbacks.

Architecture and UML diagrams are provided in architecture.md.

## 6. Implementation
The driver starts with a temperature of 25 degrees Celsius.

Reading returns the temperature as text. Writing accepts integer
values from -40 to 125 degrees Celsius.

Malformed, oversized, and out-of-range input is rejected.
A rejected update leaves the stored value unchanged.

A mutex protects access to the shared temperature.
Kernel copy helpers transfer data between user and kernel space.

The C++ application displays one reading per execution.
Shell commands are used to update the temperature.

## 7. Development Process
Development began with environment setup and a test kernel module.
The virtual device, read/write operations, and C++ application
were then implemented and integrated.

The initial driver work used a development branch that was merged
into main. Source code and documentation were uploaded to GitHub.

Requirements and architecture documents were prepared after the
initial prototype. Progress notes record the work performed.

## 8. Testing and Results
Ten manual tests were completed successfully:

1. Minimum accepted temperature: -40 C.
2. Maximum accepted temperature: 125 C.
3. Rejection of 126.
4. Rejection of -41.
5. Rejection of non-numeric text.
6. Rejection of oversized input.
7. Application error when the driver is unavailable.
8. Temperature reset to 25 C after module reload.
9. Permission-denied error without sudo.
10. Basic concurrent reading and writing.

During concurrent testing, 20 application readings returned
30 C or 40 C while a background process updated the device.
No application or write errors were visible.

The reviewed kernel-log excerpt contained BTF warnings but
no visible vtemp crash or stack trace.

Full results and test limitations are recorded in testing.md.

## 9. Challenges and Observations
- Driver compilation required a compatible kernel build environment.
- Module-loading BTF warnings were observed and documented.
  Loading and the listed functional tests still succeeded.
- Device permissions required elevated access for normal operation.
- Invalid writes produced shell errors, which were expected
  during rejection tests.

## 10. Achievements
The project demonstrates:
- Linux module loading and unloading.
- Character-device registration and file-operation callbacks.
- User-space and kernel-space communication.
- Input validation and mutex synchronization.
- C++ classes, constructors, encapsulation, and exceptions.
- Git version control and project documentation.

## 11. Limitations
- The sensor is simulated.
- Only one integer temperature is stored.
- The application reads once per execution.
- Updates currently use shell commands.
- Unloading the module loses the stored value.
- Device access normally requires root privileges.
- The concurrency test is limited.
- Multiple partial reads do not preserve a fixed snapshot
  when another process updates the value between reads.
- Hardware interrupts and physical sensor communication
  are not implemented.

## 12. Future Improvements
- Add temperature updates to the C++ application.
- Add periodic readings and temperature alerts.
- Save readings with timestamps.
- Expand automated testing using C or C++.
- Adapt the driver for a physical sensor.

## 13. Conclusion
The prototype demonstrates a working Linux virtual device
and a C++ application that reads from it.

The listed tests verified basic operation, input rejection,
application errors, reload behaviour, and limited concurrent access.
The final evaluation and project demonstration remain to be completed.

## 14. Supporting Documents
- [Requirements](requirements.md)
- [Architecture and UML](architecture.md)
- [Testing](testing.md)
- [Progress](progress.md)
- [Build and Execution Instructions](../README.md)
