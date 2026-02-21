#include <stdio.h>
#include <pthread.h>

void *run()
{
  printf("child: hello!\n");
  printf("child: goodbye\n");

  return NULL;
}

int main()
{
  pthread_t thread;

  printf("parent: hello!\n");
  pthread_create(&thread, NULL, run, NULL);

  pthread_join(thread, NULL);
  
  printf("parent: goodbye\n");
}

