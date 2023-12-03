#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_handler(int signum) {
  printf("Ctrl+C pressed!\n");
  exit(0);
}

int main() {
  // Change the default function of Ctrl+C
  signal(SIGINT, my_handler);

  // Do something
  printf("Doing something...\n");

  // Restore the default function of Ctrl+C
  signal(SIGINT, SIG_DFL);

  // Do something else
  printf("Doing something else...\n");

  return 0;
}
