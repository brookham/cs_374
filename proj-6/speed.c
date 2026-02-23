#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <errno.h>

int speed = 0;
volatile sig_atomic_t speed_adjust = 0;

void speed_handler(int sig)
{
  if (sig == SIGUSR2)
    speed_adjust = 1;
  if (sig == SIGUSR1)
    speed_adjust = -1;
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

    if (speed_adjust != 0)
    {
      if (speed_adjust == 1)
      {
        speed += 1;
        printf("increased speed to: %d\n", speed);
      }
      if (speed_adjust == -1 && speed > 0)
      {
        speed -= 1;
        printf("decreased speed to: %d\n", speed);
      }
      else if (speed_adjust == -1 && speed == 0)
      {
        printf("decreased speed to: %d\n", speed);
      }
      speed_adjust = 0;
    }

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
            printf("increased speed to: %d\n", speed);
          }
          if (buf[i] == '-' && speed > 0)
          {
            speed -= 1;
            printf("decreased speed to: %d\n", speed);
          }
          if (buf[i] == '-' && speed == 0)
          {
            printf("decreased speed to: %d\n", speed);
          }
          else if (buf[i] == 'q')
          {
            return 0;
          }
        }
      }
    }
  }
}