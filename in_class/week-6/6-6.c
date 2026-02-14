#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <errno.h>

volatile sig_atomic_t flag;

void sigusr1_handler(int sig)
{
  (void)sig;
  flag = 1;
}

int main(void)
{
  struct sigaction sa = {
    .sa_handler = sigusr1_handler,
    .sa_flags = 0,
  };
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);

  sigset_t mask, oldmask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);

  sigprocmask(SIG_BLOCK, &mask, &oldmask);

  sigset_t zero;
  sigemptyset(&zero);

  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(0, &readfds);

  printf("Either enter some text, or ...\n");
  printf("Go to another window and `kill -USR1 %d`.\n", getpid());


  int count = STDIN_FILENO + 1;

  int p = pselect(
    count,
    &readfds,
    NULL,
    NULL,
    NULL,
    &zero

  );
  char buf[128];
  

  if (p > 0){
    if (FD_ISSET(0, &readfds)){
      ssize_t stuff = read(0, buf, 128);
      write(1, buf, (ssize_t)stuff);
    }
  }else if (p == -1 && errno == EINTR){
    if (flag){
      printf("Got SIGUSR1\n");
    }
  }


}