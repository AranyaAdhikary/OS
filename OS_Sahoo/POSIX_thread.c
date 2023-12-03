#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *child_thread_function(void *arg) {
  printf("Child thread started\n");
  sleep(2);
  printf("Child thread finished\n");

  return NULL;
}

int main() {
  pthread_t child_thread;
  if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0) {
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  if (pthread_join(child_thread, NULL) != 0) {
    perror("pthread_join");
    exit(EXIT_FAILURE);
  }

  printf("Main thread finished waiting for child thread\n");

  return EXIT_SUCCESS;
}
