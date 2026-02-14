#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sigusr1_handler(int sig)

{
  (void)sig;
  write(1, "SIGUSR1 handled\n", 16);
}

int main(void)
{
  struct sigaction sa = {
    .sa_handler = sigusr1_handler,
    .sa_flags = SA_RESTART,
  };
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);

  sigset_t mask, oldmask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);

  sigprocmask(SIG_BLOCK, &mask, &oldmask);

  printf("SIGUSR1 is blocked.");
  printf("Reading from the keuboard but dont type anything.");
  printf("Go to another window and `kill -USR1 %d` several times.\n", getpid());
  printf("Then press RETURN to continue.\n");

  char buf[12];
  read(0, buf, 12);

  sigprocmask(SIG_UNBLOCK, &mask, &oldmask);

  printf("Signal unblocked.\n");


  //thats because while the signalls are bing blocked they are
  //they are being combined into one signal instead of being counted
  //and piling up
}