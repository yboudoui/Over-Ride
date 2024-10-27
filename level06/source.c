#include <stdio.h>
#include <string.h>
#include <unistd.h>  // for `ptrace`
#include <sys/ptrace.h>

int auth(char *username, int serial) {
    int calculated_serial; // Holds the computed serial value
    int username_len;      // Length of the input username

    // Remove newline character from username
    username[strcspn(username, "\n")] = '\0';

    // Get length of the username, with a maximum of 32 characters
    username_len = strnlen(username, 32);
    
    // If username is 5 characters or fewer, authentication fails
    if (username_len <= 5) {
        return 1;
    }

    // Anti-debugging check: detect if debugger is attached
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        puts("\x1B[32m.---------------------------.");
        puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1B[32m'---------------------------'");
        return 1;
    }

    // Initialize calculated serial using the 4th character of username
    calculated_serial = (username[3] ^ 0x1337) + 6221293;

    // Loop through each character in the username to update `calculated_serial`
    for (int i = 0; i < username_len; ++i) {
        // Check for control characters; if found, authentication fails
        if (username[i] <= 31) {
            return 1;
        }

        // Update `calculated_serial` based on each character in username
        calculated_serial += (calculated_serial ^ (unsigned int)username[i]) % 0x539;
    }

    // Authentication succeeds only if the calculated serial matches the provided serial
    return serial != calculated_serial;
}

int main() {
    char username[28];      // Buffer for storing the username
    int serial;             // Variable to hold the user-provided serial

    // Print welcome banner
    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    // Prompt user for their login name
    printf("-> Enter Login: ");
    fgets(username, sizeof(username), stdin);

    // Inform user of new account detection
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    // Prompt user for their serial number
    printf("-> Enter Serial: ");
    scanf("%d", &serial);

    // Attempt to authenticate using provided username and serial
    if (auth(username, serial)) {
        // If authentication fails, exit with failure code
        return 1;
    }

    // If authentication succeeds, grant access by opening a shell
    puts("Authenticated!");
    system("/bin/sh");

    return 0;
}
