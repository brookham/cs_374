#include <stdio.h>
#include <pthread.h>

struct messages {
  char *hello;
  char *goodbye;
};

void *run(void *arg)
{
  struct messages *msgs = (struct messages *)arg;
  
  printf("child: %s\n", msgs->hello);
  printf("child: %s\n", msgs->goodbye);

  return NULL;
}

int main()
{
  pthread_t thread;
  
  struct messages msgs = {
    .hello = "custom hello!",
    .goodbye = "custom goodbye"
  };

  printf("parent: hello!\n");
  pthread_create(&thread, NULL, run, &msgs);

  pthread_join(thread, NULL);
  
  printf("parent: goodbye\n");
}
