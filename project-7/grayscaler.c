#include "ppm.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *run(void *arg)
{
  struct ppm *img_info = (struct ppm *)arg;

  printf("%d\n", img_info->height);

  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 1){
    printf("nah\n");
  }

  struct ppm *img_info = ppm_read(argv[2]);

  int num_threads = atoi(argv[1]);

  pthread_t thread[num_threads];

  for (int i = 0; i < num_threads; i++){
    pthread_create(thread + i, NULL, run, img_info);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(thread[i], NULL);
  }
  
  printf("parent: goodbye\n");
}