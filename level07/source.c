#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to get an unsigned integer from the user
unsigned int get_unum() {
    unsigned int input;
    fflush(stdout);
    scanf("%u", &input); // Expect an unsigned integer
    getchar(); // Clear the newline character from input buffer
    return input;
}

// Function to store a number at a specific index in an array
int store_number(int *data_storage) {
    unsigned int number, index;

    // Get the number to store
    printf(" Number: ");
    number = get_unum();

    // Get the index where the number should be stored
    printf(" Index: ");
    index = get_unum();

    // Check if index is restricted (multiple of 3 or high byte of number == 183)
    if (index % 3 == 0 || (number >> 8) == 183) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1; // Indicate failure
    } else {
        data_storage[index] = number; // Store the number at the specified index
        return 0; // Indicate success
    }
}

// Function to read a number from a specific index in the array
int read_number(int *data_storage) {
    unsigned int index;

    // Get the index from which to read
    printf(" Index: ");
    index = get_unum();

    // Display the number stored at the given index
    printf(" Number at data[%u] is %u\n", index, data_storage[index]);
    return 0; // Indicate success
}

int main(int argc, char **argv, char **envp) {
    int data_storage[100]; // Array to store numbers
    char command[20];
    int result;

    // Initialize variables and clear sensitive data from arguments and environment
    memset(data_storage, 0, sizeof(data_storage));
    while (*argv) {
        memset(*argv, 0, strlen(*argv));
        ++argv;
    }
    while (*envp) {
        memset(*envp, 0, strlen(*envp));
        ++envp;
    }

    // Display the program banner
    puts("----------------------------------------------------");
    puts("  Welcome to wil's crappy number storage service!   ");
    puts("----------------------------------------------------");
    puts(" Commands:                                          ");
    puts("    store - store a number into the data storage    ");
    puts("    read  - read a number from the data storage     ");
    puts("    quit  - exit the program                        ");
    puts("----------------------------------------------------");
    puts("   wil has reserved some storage :>                 ");
    puts("----------------------------------------------------");

    // Main program loop
    while (1) {
        printf("Input command: ");
        fgets(command, sizeof(command), stdin); // Read command from user
        command[strcspn(command, "\n")] = 0; // Remove newline character

        // Handle "store" command
        if (strcmp(command, "store") == 0) {
            result = store_number(data_storage);
        }
        // Handle "read" command
        else if (strcmp(command, "read") == 0) {
            result = read_number(data_storage);
        }
        // Handle "quit" command
        else if (strcmp(command, "quit") == 0) {
            break; // Exit the program
        }
        // Handle unknown commands
        else {
            printf("Unknown command: %s\n", command);
            continue;
        }

        // Display whether the command was successful
        if (result) {
            printf(" Failed to execute %s command\n", command);
        } else {
            printf(" Completed %s command successfully\n", command);
        }
    }

    return 0;
}
