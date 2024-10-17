#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv, const char **envp) {
  char password[96];
  char read_buffer[48];
  char username[96];
  int read = 0;
  FILE *stream = 0;

  memset(username, 0, sizeof(username));
  memset(password, 0, sizeof(password));

  memset(read_buffer, 0, 41);
  stream = fopen("/home/users/level03/.pass", "r");
  if (!stream) {
    fwrite("ERROR: failed to open password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  read = fread(read_buffer, 1, 41, stream);
  read_buffer[strcspn(read_buffer, "\n")] = 0;
  if (read != 41) {
    fwrite("ERROR: failed to read password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  fclose(stream);

  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(username, 100, stdin);
  username[strcspn(username, "\n")] = 0;
  printf("--[ Password: ");
  fgets(password, 100, stdin);
  password[strcspn(password, "\n")] = 0;
  puts("*****************************************");

  if (strncmp(read_buffer, password, 41)) {
    printf(username);
    puts(" does not have access!");
    exit(1);
  }

  printf("Greetings, %s!\n", username);
  system("/bin/sh");
  return 0;
}
