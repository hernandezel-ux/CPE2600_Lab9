
/************************************************************
 * Filename: finfo.c
 * Author: Emanuel Hernandez
 * Assignment: CPE-2600 Lab 9 - System Calls
 * Section: 111
 * Description: Displays file information including type,
 *              permissions, owner, size, and modification
 *              date and time.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat file;
    char *type;
    char permissions[10];
    char modified[100];
    struct tm *time_info;

    // Check that a filename was provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file information
    if (lstat(argv[1], &file) == -1) {
        perror("Error getting file information");
        return 1;
    }

    // Determine the type of file
    if (S_ISREG(file.st_mode)) {
        type = "Regular File";
    }
    else if (S_ISDIR(file.st_mode)) {
        type = "Directory";
    }
    else if (S_ISLNK(file.st_mode)) {
        type = "Symbolic Link";
    }
    else if (S_ISCHR(file.st_mode)) {
        type = "Character Device";
    }
    else if (S_ISBLK(file.st_mode)) {
        type = "Block Device";
    }
    else if (S_ISFIFO(file.st_mode)) {
        type = "FIFO";
    }
    else if (S_ISSOCK(file.st_mode)) {
        type = "Socket";
    }
    else {
        type = "Unknown";
    }

    // Determine file permissions
    permissions[0] = (file.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[1] = (file.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[2] = (file.st_mode & S_IXUSR) ? 'x' : '-';

    permissions[3] = (file.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[4] = (file.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[5] = (file.st_mode & S_IXGRP) ? 'x' : '-';

    permissions[6] = (file.st_mode & S_IROTH) ? 'r' : '-';
    permissions[7] = (file.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[8] = (file.st_mode & S_IXOTH) ? 'x' : '-';

    permissions[9] = '\0';

    // Convert modification time to readable format
    time_info = localtime(&file.st_mtime);

    if (time_info == NULL) {
        perror("Error converting modification time");
        return 1;
    }

    if (strftime(modified, sizeof(modified),
                 "%Y-%m-%d %H:%M:%S", time_info) == 0) {
        fprintf(stderr, "Error formatting modification time\n");
        return 1;
    }

    // Print file information
    printf("File Name: %s\n", argv[1]);
    printf("File Type: %s\n", type);
    printf("Permissions: %s\n", permissions);
    printf("Owner ID: %lu\n", (unsigned long)file.st_uid);
    printf("File Size: %lld bytes\n", (long long)file.st_size);
    printf("Last Modified: %s\n", modified);

    return 0;
}
