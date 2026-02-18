#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 10
int big_arr[10000] = {0};

void *run(void *args)
{
  for (int count = 0; count < 10000; count++){
    big_arr[count]++;
  }
  return NULL;
}

int main(){
  pthread_t thread[THREAD_COUNT];
  int thread_id[THREAD_COUNT];

  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(thread + i, NULL, run, NULL);
  }

  for (int count = 0; count < 10000; count++){
    printf("%d = %d, expected 10\n", count, big_arr[count]);
  }


  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(thread[i], NULL);
  }

  puts("yippy\n");

}