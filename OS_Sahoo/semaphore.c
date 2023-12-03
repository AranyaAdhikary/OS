#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void lock(sem_t *sem) {
  sem_wait(sem);
}

void unlock(sem_t *sem) {
  sem_post(sem);
}

void * thread_function(void *arg) {
  lock(&semaphore);
  printf("Inside the critical section of the thread with thread ID: %d\n" , pthread_self()) ;
  unlock(&semaphore);
}

int main() {
  sem_init(&semaphore, 0, 1);
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, thread_function, NULL);
  pthread_create(&thread2, NULL, thread_function, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  sem_destroy(&semaphore);
  return 0;
}
