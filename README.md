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
          | open(), read(), write()
          v
      /dev/vtemp
          |
          v
Linux Virtual Temperature Device Driver
          |
          v
  Simulated Temperature Data
