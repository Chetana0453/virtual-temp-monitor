# Virtual Temperature Sensor Monitoring System

## 1. Project Overview

This project implements a virtual temperature sensor using a Linux character device driver and a C++ user-space application.

The Linux device driver creates a device file named `/dev/vtemp`. The C++ application reads the simulated temperature from this device and displays it on the terminal.

## 2. Objectives

- Understand Linux device-driver development.
- Create and register a character device.
- Read and update simulated sensor data.
- Use Linux system calls such as `open()`, `read()`, and `write()`.
- Develop a C++ application using object-oriented programming.
- Demonstrate communication between user space and kernel space.

## 3. Technologies Used

- Linux on WSL2
- C and Linux Kernel Module
- C++17
- Linux system calls
- Git and GitHub
- GCC and GCC-11

## 4. System Architecture

```text
C++ Monitoring Application
          |
          | open(), read()
          v
      /dev/vtemp
          |
          v
Linux Virtual Temperature Device Driver
          |
          v
  Simulated Temperature Data
```

## 5. Features

- Creates the Linux character device `/dev/vtemp`.
- Stores a simulated temperature, initially 25 degrees Celsius.
- Supports reading and updating the temperature through the driver.
- Accepts integer temperatures from -40 to 125 degrees Celsius.
- Rejects out-of-range updates without changing the stored value.
- Uses a mutex to protect access to the temperature.
- Displays one temperature reading through a C++ application.

## 6. Project Files

- `driver/vtemp.c`: Virtual temperature device driver written in C.
- `driver/hello.c`: Initial kernel module used for environment testing.
- `driver/Makefile`: Kernel module build configuration.
- `app/monitor.cpp`: C++ application that reads the temperature.
- `docs/progress.md`: Development progress notes.
- `.gitignore`: Excludes generated build files from Git.
- `README.md`: Project overview and execution instructions.

## 7. Build Instructions

### Prerequisites

- Ubuntu on WSL2.
- Tested kernel: `6.6.87.2-microsoft-standard-WSL2`.
- GCC-11, G++, Make, and kernel build dependencies.
- A configured and built matching kernel source tree at
  `~/kernel-build/WSL2-Linux-Kernel`, including `Module.symvers`.

The driver must be built against a kernel configuration and version
compatible with the running kernel. This source directory is an
external prerequisite and is not included in this repository.

Run the following commands from the project directory:

```bash
cd ~/virtual-temp-monitor
```

Build the kernel modules:

```bash
make -C ~/kernel-build/WSL2-Linux-Kernel \
M="$PWD/driver" CC=gcc-11 LOCALVERSION= modules
```

Build the C++ application:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
app/monitor.cpp -o app/monitor
```
## 8. Run Instructions

Run these commands from the project directory.

Load the driver if it is not already loaded:

```bash
sudo insmod driver/vtemp.ko
```

Check that the device exists:

```bash
ls -l /dev/vtemp
```

Run the C++ application:

```bash
sudo ./app/monitor
```

After a fresh driver load, the expected output is:

```text
Virtual Temperature: 25 C
```

Update the simulated temperature through the shell:

```bash
sudo sh -c 'printf "42\n" > /dev/vtemp'
```

Read the updated value through the C++ application:

```bash
sudo ./app/monitor
```

Expected output:

```text
Virtual Temperature: 42 C
```

The device uses permissions `0600`, so these operations require root
access through `sudo`.

When finished, unload the driver:

```bash
sudo rmmod vtemp
```

Unloading removes `/dev/vtemp`. Loading the driver again resets the
simulated temperature to 25 degrees Celsius.

## 9. Testing and Results

The following manual tests were completed:

| Test | Observed result |
| --- | --- |
| Load the driver | `/dev/vtemp` was created |
| Read the initial temperature | Returned 25 |
| Write 37 and read again | Returned 37 |
| Write the invalid value 200 | Write failed; temperature remained 37 |
| Run the C++ application after loading | Displayed 25 C |
| Write 42 and run the application | Displayed 42 C |
| Unload the driver | `/dev/vtemp` was removed |

A BTF debug-information mismatch warning was observed during module
testing. Module loading and the tested read/write operations succeeded.

These tests verify basic functionality. Boundary-value, malformed-input,
and concurrent-access tests remain to be completed.

## 10. Limitations

- Temperature values are simulated; no physical sensor is connected.
- The C++ application reads and displays one value per execution.
- Temperature updates currently use shell commands.
- Device access requires root privileges.
- The stored temperature resets when the driver is reloaded.
- Building the driver requires a compatible kernel build environment.

## 11. Future Improvements

- Add temperature updates through the C++ application.
- Add periodic monitoring and configurable temperature warnings.
- Save readings with timestamps.
- Extend automated testing.
- Explore integration with a physical temperature sensor.
