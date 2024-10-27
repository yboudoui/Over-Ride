#include <stdio.h>
#include <string.h>
#include <unistd.h>  // for `ptrace`
#include <sys/ptrace.h>

int auth() {
    unsigned int serial;        // Calculated serial number for authentication
    unsigned int input_len;     // Length of the user-provided login name
    unsigned int auth_value;    // Intermediate calculated value used in the authentication loop
    char login[32];             // Buffer for the login name (up to 31 characters + null terminator)
    char check_byte;            // Single byte for comparison at the end

    // Remove newline from login
    login[strcspn(login, "\n")] = '\0';

    // Calculate the length of the login name, with a max length of 32
    input_len = strnlen(login, 32);
    if (input_len <= 5) {
        // Login must be more than 5 characters
        return 1;
    }

    // Check for a debugger; if detected, exit early
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        puts("Debugging detected! Exiting.");
        return 1;
    }

    // Initialize serial number with a specific calculation based on the 4th character of the login
    auth_value = (login[3] ^ 4919) + 6221293;

    // Loop over each character in the login name to perform further calculations
    for (unsigned int i = 0; i < input_len; i++) {
        unsigned int temp_value = login[i] ^ auth_value;
        auth_value += temp_value - (((temp_value * 2284010283U) >> 32) >> 1) * 1337;
    }

    // The `check_byte` should match the final `auth_value` for successful authentication
    return (check_byte == auth_value) ? 0 : 1;
}

int main() {
    char login[32];         // Buffer to store the user login name
    unsigned int serial;    // User-provided serial number

    // Print the welcome banner
    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    // Prompt for login name and read user input
    printf("-> Enter Login: ");
    fgets(login, sizeof(login), stdin);

    // Inform the user of a new account detection
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    // Prompt for the serial number and read it
    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    // Check if authentication succeeds
    if (auth() == 0) {
        puts("Authenticated!");
        system("/bin/sh");  // Give the user a shell on successful authentication
    } else {
        puts("Authentication failed!");
    }

    return 0;
}
