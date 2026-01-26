#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void main()
{
  int pipe_fd[2];
  char buf[128];
  
  pipe(pipe_fd);

  write(pipe_fd[1], "hello\n", 6);
  read(pipe_fd[0], buf, 6);
  write(STDOUT_FILENO, buf, 6);
}