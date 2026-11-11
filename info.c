
/************************************************************
 * Filename: info.c
 * Author: Emanuel Hernandez
 * Assignment: CPE-2600 Lab 9 - System Calls
 * Section: 111
 * Description: Displays system information including
 *              time, OS, CPU count, and memory usage.
 ************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[])
{
    struct timespec ts;
    struct utsname system;
    struct sysinfo memory;
    char hostname[256];
    long cpus;
    long pages;
    long page_size;

    // Get current time in nanoseconds
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("Error getting time");
        return 1;
    }

    printf("Current Time (nanoseconds): %lld\n",
           (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec);

    // Get system network name
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("Error getting hostname");
        return 1;
    }

    hostname[sizeof(hostname) - 1] = '\0';

    if (hostname[0] != '\0') {
        printf("Network Name: %s\n", hostname);
    }

    // Get operating system information
    if (uname(&system) == -1) {
        perror("Error getting system information");
        return 1;
    }

    if (system.sysname[0] != '\0') {
        printf("Operating System: %s\n", system.sysname);
    }

    if (system.release[0] != '\0') {
        printf("OS Release: %s\n", system.release);
    }

    if (system.version[0] != '\0') {
        printf("OS Version: %s\n", system.version);
    }

    if (system.machine[0] != '\0') {
        printf("Hardware Type: %s\n", system.machine);
    }

    // Get number of CPUs
    cpus = get_nprocs();

    if (cpus > 0) {
        printf("Number of CPUs: %ld\n", cpus);
    }

    // Get physical memory using sysconf and getpagesize
    pages = sysconf(_SC_PHYS_PAGES);
    page_size = getpagesize();

    if (pages > 0 && page_size > 0) {
        printf("Total Physical Memory: %llu bytes\n",
               (unsigned long long)pages * page_size);
    }

    // Get free physical memory
    if (sysinfo(&memory) == -1) {
        perror("Error getting memory information");
        return 1;
    }

    printf("Free Physical Memory: %llu bytes\n",
           (unsigned long long)memory.freeram *
           memory.mem_unit);

    return 0;
}
