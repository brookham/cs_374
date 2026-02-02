#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int pipe_fd[2];
  pipe(pipe_fd);

  pid_t pid = fork();
  
  char *dir = (argc >= 2) ? argv[1] : ".";

  if (pid == 0){
    dup2(pipe_fd[0], 0);
    close(pipe_fd[1]);
    execlp("wc", "wc", "-l", NULL);

  }
  else if (pid > 0){
    dup2(pipe_fd[1], 1);
    close(pipe_fd[0]);
    execlp("ls", "ls", "-1a", dir, NULL);

  }
  
  return 0;
}