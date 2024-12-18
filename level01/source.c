#include <stdio.h>
#include <string.h>

char username_buffer[100];

int verify_user_name()
{
  puts("verifying username....\n");
  return memcmp(username_buffer, "dat_wil", 7) != 0;
}

int verify_user_pass(const void *password_buffer)
{
  return memcmp(password_buffer, "admin", 5) != 0;
}

int  main(int argc, const char **argv, const char **envp)
{
  char password_buffer[64];
  int is_username_ok;

  memset(password_buffer, 0, sizeof(password_buffer));
  is_username_ok = 0;

  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");

  fgets(username_buffer, 256, stdin);
  is_username_ok = verify_user_name();
  if ( is_username_ok )
  {
    puts("nope, incorrect username...\n");
  }
  else
  {
    puts("Enter Password: ");
    fgets(password_buffer, 100, stdin);
    verify_user_pass(password_buffer);
    puts("nope, incorrect password...\n");
  }
  return 1;
}
