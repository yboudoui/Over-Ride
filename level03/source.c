#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int decrypt(char a1) {
  unsigned int i;
  unsigned int v3;
  char v4[29];

  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for (i = 0; i < v3; ++i)
    v4[i] ^= a1;
  if (!strcmp(v4, "Congratulations!"))
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}

int test(int a1, int a2) {
  char v = a2 - a1;
  if (v >= 1 && v <= 21)
    return decrypt(v);
  return decrypt(rand());
}

int main(int argc, const char **argv, const char **envp) {
  unsigned int v3;
  int savedregs;

  v3 = time(0);
  srand(v3);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &savedregs);
  test(savedregs, 322424845);
  return 0;
}
