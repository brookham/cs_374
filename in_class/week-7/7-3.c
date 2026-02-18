#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 10

void *run(void *args)
{
  int *id = args;
  printf("running %d\n", *id);
  return NULL;
}

int main(){
  pthread_t thread[THREAD_COUNT];
  int thread_id[THREAD_COUNT];

  for (int i = 0; i < THREAD_COUNT; i++) {
    thread_id[i] = i;
    pthread_create(thread + i, NULL, run, thread_id + i);
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(thread[i], NULL);
  }

  puts("yippy\n");

}