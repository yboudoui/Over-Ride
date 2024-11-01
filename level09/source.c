#include <stdio.h>
#include <string.h>

// Reads a command from stdin and executes it, making it a potential security risk.
void secret_backdoor(void) {
    char command_buffer[128];

    // Get user input and store it in the command buffer (size limit: 128)
    fgets(command_buffer, 128, stdin);

    // Execute the command, risky as it allows arbitrary command execution
    system(command_buffer);
}


// Handles a message by setting up the username and message buffers
void handle_msg(void) {
    char message_buffer[140];
    long padding1 = 0, padding2 = 0, padding3 = 0, padding4 = 0;
    int message_length = 140;

    // Set up username and message, then confirm message sent
    set_username(message_buffer);
    set_msg(message_buffer);
    puts(">: Msg sent!");
}


// Sets up the message content with an input buffer, copying input to the message buffer
void set_msg(char *message_buffer) {
    char input_buffer[1024];

    // Clear the input buffer (1024 bytes) by zeroing out each 8-byte block
    memset(input_buffer, 0, 1024);

    puts(">: Msg @Unix-Dude");
    printf(">>: ");

    // Get message input from user and store in input buffer (limit: 1024 bytes)
    fgets(input_buffer, 1024, stdin);

    // Copy input buffer content to message buffer with limit from specified length
    strncpy(message_buffer, input_buffer, (long) *(int *)(message_buffer + 180));
}


// Sets up the username by reading input and copying it into the username buffer
void set_username(char *username_buffer) {
    char input_buffer[140];
    int username_length;

    // Clear input buffer (140 bytes) by zeroing out each 8-byte block
    memset(input_buffer, 0, 140);

    puts(">: Enter your username");
    printf(">>: ");

    // Get username input from user and store in input buffer (limit: 128 bytes)
    fgets(input_buffer, 128, stdin);

    // Copy input buffer content to username buffer until end of input or limit (41 bytes)
    for (username_length = 0; username_length < 41 && input_buffer[username_length] != '\0'; username_length++) {
        username_buffer[username_length + 140] = input_buffer[username_length];
    }

    printf(">: Welcome, %s", username_buffer);
}


int main(void) {
    // Display welcome banner
    puts(
        "--------------------------------------------\n"
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
        "--------------------------------------------"
    );

    // Begin handling message (sets up username and message)
    handle_msg();
    return 0;
}
