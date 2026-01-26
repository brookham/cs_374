#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void main()
{
  int pipe_fd[2];
  char buf[128] = {0};
  
  pid_t pid;

  pipe(pipe_fd);

  pid  = fork();

  if (pid == 0){
    close(pipe_fd[0]);
    write(pipe_fd[1], "hello, parent!\n", 15);
    exit(1);
  }else {
    close(pipe_fd[1]);
    read(pipe_fd[0], buf, sizeof buf);
    write(STDOUT_FILENO, buf, sizeof buf);
    close(pipe_fd[0]);

    wait(NULL);
  }


  
  
}