#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, const char **argv, const char **envp) {
    int status;           // To store the status of the child process
    char buffer[128];     // Buffer to hold user input
    int syscall_number;   // For holding the result of ptrace syscall number
    __pid_t child_pid;    // PID of the forked child process

    // Fork a new process
    child_pid = fork();

    // Initialize the buffer and variables
    memset(buffer, 0, sizeof(buffer));
    syscall_number = 0;
    status = 0;

    if (child_pid) {  // Parent process
        do {
            // Wait for the child process to change state
            wait(&status);

            // Check if the child exited normally or received a fatal signal
            if ((status & 0x7F) == 0 || ((status & 0x7F) + 1) >> 1 > 0) {
                puts("Child is exiting...");
                return 0;
            }

            // Use ptrace to check the system call being executed by the child
            syscall_number = ptrace(PTRACE_PEEKUSER, child_pid, 44, 0);
        } while (syscall_number != 11);  // Loop until `exec()` is attempted

        // If `exec()` is detected, terminate the child
        puts("No exec() for you");
        kill(child_pid, SIGKILL);

    } else {  // Child process
        // Set up the process to be traced by the parent
        prctl(PR_SET_PDEATHSIG, SIGKILL); // Ensure child dies if parent exits
        ptrace(PTRACE_TRACEME, 0, 0, 0);

        // Prompt the user for input
        puts("Give me some shellcode, k");

        // Read input into the buffer (vulnerable to buffer overflow)
        gets(buffer);
    }

    return 0;
}
