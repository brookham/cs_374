#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sigint_handler(int sig)
{
    (void)sig;
    const char msg[] = "Got SIGINT!\n";
    write(1, msg, sizeof msg  - 1);
}


int main(void)
{
  char s[200];
  struct sigaction sa = {
    .sa_handler = sigint_handler,
    .sa_flags = 0,
  };

  sigemptyset(&sa.sa_mask);

  sigaction(SIGINT, &sa, NULL);

  printf("Program will exit in 10 seconds. Hit ^C!\n");
  int value = sleep(10);
  printf("%d\n", value);
}