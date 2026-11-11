/************************************************************
 * Filename: pinfo.c
 * Author: Emanuel Hernandez
 * Assignment: CPE-2600 Lab 9 - System Calls
 * Section: 111
 * Description: Displays process priority and scheduling
 *              method for a specified process.
 ************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int priority;
    int scheduler;
    char *method;

    // Check command line arguments
    if (argc > 2) {
        printf("Usage: %s [PID]\n", argv[0]);
        return 1;
    }

    // Use specified PID or current process PID
    if (argc == 2) {
        char *end;
        long value = strtol(argv[1], &end, 10);

        if (*argv[1] == '\0' || *end != '\0' ||
            value <= 0 || value > INT_MAX) {
            fprintf(stderr, "Error: Invalid PID\n");
            return 1;
        }

        pid = (pid_t)value;
    }
    else {
        pid = getpid();
    }

    // Get scheduling method and check if process exists
    scheduler = sched_getscheduler(pid);

    if (scheduler == -1) {
        perror("Error getting scheduler");
        return 1;
    }

    // Get process priority
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);

    if (errno != 0) {
        perror("Error getting priority");
        return 1;
    }

    // Convert scheduling method to readable text
    switch (scheduler) {
        case SCHED_OTHER:
            method = "SCHED_OTHER";
            break;
        case SCHED_FIFO:
            method = "SCHED_FIFO";
            break;
        case SCHED_RR:
            method = "SCHED_RR";
            break;
        case SCHED_BATCH:
            method = "SCHED_BATCH";
            break;
        case SCHED_IDLE:
            method = "SCHED_IDLE";
            break;
        default:
            method = "Unknown";
            break;
    }

    // Print process information
    printf("Process ID: %ld\n", (long)pid);
    printf("Process Priority: %d\n", priority);
    printf("Scheduling Method: %s\n", method);

    return 0;
}
