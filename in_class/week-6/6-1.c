#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(void)
{
  char s[200];
  struct sigaction sa = {
    .sa_handler = SIG_IGN,
    .sa_flags = 0,
  };

  sigemptyset(&sa.sa_mask);

  sigaction(SIGINT, &sa, NULL);

  printf("^C locked out for 5 seconds! Try it!\n");
  sleep(5);

  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, NULL);

  printf("^C reenabled! Try it!\n");
  sleep(10);
}