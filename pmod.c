
/************************************************************
 * Filename: pmod.c
 * Author: Emanuel Hernandez
 * Assignment: CPE-2600 Lab 9 - System Calls
 * Section: 111
 * Description: Reduces the process priority by 10,
 *              sleeps for a specified time, and exits.
 ************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    struct timespec sleep_time;
    struct timespec remaining;
    int priority;

    // Print current process ID
    printf("Process ID: %ld\n", (long)getpid());

    // Reduce scheduling priority by increasing nice value by 10
    errno = 0;
    priority = nice(10);

    if (priority == -1 && errno != 0) {
        perror("Error changing priority");
        return 1;
    }

    printf("New nice value: %d\n", priority);

    // Sleep for 1,837,272,638 nanoseconds
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638;

    printf("Sleeping for 1,837,272,638 nanoseconds...\n");
    fflush(stdout);

    // Continue sleeping if interrupted by a signal
    while (nanosleep(&sleep_time, &remaining) == -1) {
        if (errno == EINTR) {
            sleep_time = remaining;
        }
        else {
            perror("Error sleeping");
            return 1;
        }
    }

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}
