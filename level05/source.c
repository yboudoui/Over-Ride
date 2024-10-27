#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t main(int32_t argc, char** argv, char** envp) {
    char buffer[100];         // Buffer to store user input (was 'var_78')
    int32_t index = 0;        // Variable to track the position in the loop (was 'var_14_1')

    // Read up to 99 characters from user input (plus null terminator) into buffer
    fgets(buffer, 100, stdin);

    // Loop over each character in the buffer until reaching the null terminator
    while (buffer[index] != '\0') {
        
        // Check if character is an uppercase letter (ASCII range 'A' (0x41) to 'Z' (0x5A))
        if (buffer[index] >= 'A' && buffer[index] <= 'Z') {
            buffer[index] ^= 0x20;  // Convert to lowercase by toggling the 6th bit
        }
        
        index++;
    }
    
    // Print the modified buffer to standard output
    printf(buffer);
    
    // Exit the program
    exit(0);
}
