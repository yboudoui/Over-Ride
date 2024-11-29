#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void log_wrapper(FILE *log_file, const char *message, const char *filename);

int main(int argc, const char **argv, const char **envp) {
    FILE *log_file;           // Log file pointer
    FILE *input_file;         // Input file pointer
    int backup_file_fd;       // File descriptor for the backup file
    char buffer;              // Buffer to hold a single character
    char backup_path[104];    // Path for the backup file

    buffer = -1;  // Initialize the buffer
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Open the log file for writing
    log_file = fopen("./backups/.log", "w");
    if (!log_file) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    // Log the start of the backup process
    log_wrapper(log_file, "Starting back up: ", argv[1]);

    // Open the input file for reading
    input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    // Construct the backup file path
    strcpy(backup_path, "./backups/");
    strncat(backup_path, argv[1], sizeof(backup_path) - strlen(backup_path) - 1);

    // Open the backup file for writing
    backup_file_fd = open(backup_path, O_WRONLY | O_CREAT | O_TRUNC, 0660);
    if (backup_file_fd < 0) {
        printf("ERROR: Failed to open %s\n", backup_path);
        exit(1);
    }

    // Copy content from the input file to the backup file
    while ((buffer = fgetc(input_file)) != EOF) {
        write(backup_file_fd, &buffer, 1);
    }

    // Log the completion of the backup process
    log_wrapper(log_file, "Finished back up ", argv[1]);

    // Close the files and cleanup
    fclose(input_file);
    close(backup_file_fd);
    fclose(log_file);

    return 0;
}
