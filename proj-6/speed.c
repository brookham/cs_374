#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <errno.h>

int speed = 0;

void speed_handler(int sig)
{
  char buf[128];
  (void)sig;
  if (sig == SIGUSR1)
  {
    speed += 1;
    int len = snprintf(buf, sizeof(buf), "increased to: %d\n", speed);
    write(1, buf, len);
  }
  else if (sig == SIGUSR2 && speed > 0)
  {
    speed -= 1;
    int len = snprintf(buf, sizeof(buf), "decreased to: %d\n", speed);
    write(1, buf, len);
  }
}

int main(int argc, char *argv[])
{
  struct sigaction sa = {
      .sa_handler = speed_handler,
      .sa_flags = 0};

  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);

  sigset_t zero;
  sigemptyset(&zero);
  printf("PID=%d\n", getpid());

  for (;;)
  {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    int count = 1;

    int p = pselect(
        count, &readfds,
        NULL,
        NULL,
        NULL,
        &zero);

    char buf[128];

    if (p > 0)
    {
      if (FD_ISSET(0, &readfds))
      {
        ssize_t stuff = read(0, buf, 128);

        for (int i = 0; i < (size_t)stuff; i++)
        {
          if (buf[i] == '+')
          {
            speed += 1;
            printf("increased to: %d\n", speed);
          }
          if (buf[i] == '-' && speed > 0)
          {
            speed -= 1;
            printf("decreased to: %d\n", speed);
          }
          if (buf[i] == 'q')
          {
            return 0;
          }
        }
      }
    }
  }
}