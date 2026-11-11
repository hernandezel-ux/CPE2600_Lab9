# CPE-2600 Lab 9 - System Calls

**Author:** Emanuel Hernandez  
**Section:** 111

## Description

This lab uses Linux system calls in C to get system information, manage processes, and display file information.

## Programs

- **info.c** - Displays system information like CPU count, memory, and OS.
- **pinfo.c** - Displays a process's priority and scheduling method.
- **pmod.c** - Changes process priority and sleeps for 1.84 seconds.
- **finfo.c** - Displays file type, permissions, owner, size, and modification date.

## How to Build

Compile all programs using:

```bash
make
```

To remove compiled files:

```bash
make clean
```

## How to Run

```bash
./info
./pinfo
./pinfo 1234
./pmod
./finfo info.c
```

For `pinfo`, the PID is optional. For `finfo`, a filename is required.

## System Calls Used

- **Information:** clock_gettime, uname, gethostname, get_nprocs, sysconf, getpagesize, sysinfo
- **Process:** getpid, getpriority, sched_getscheduler, nice, nanosleep
- **File:** lstat

## Notes

- Programs must run on Linux.
- Errors are displayed when invalid inputs are provided.
- The final GitHub repository is tagged `vFinal`.