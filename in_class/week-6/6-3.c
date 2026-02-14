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
    .sa_handler = SIG_IGN,
    .sa_flags = SA_RESTART,
  };
  sigemptyset(&sa.sa_mask);
  printf("Reading from the keyboard. But don't type anything.");
  printf("Go to another window and `kill -USR1 %d`\n", getpid());

  char buf[128];

  if (read(0, buf, 128) == -1){
    perror("read");
  }
}
// the SA_RESTART restarting syscalls instead of returning with an error

