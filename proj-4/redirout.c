#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
  if (argc < 3){
    printf("usage: redirout filename command [arg1 [arg2 ... ] ]\n");
  }
  else{
    char *outfile = argv[1];
    char *cmnd = argv[2];
    int fd = open(outfile, O_CREAT|O_TRUNC|O_WRONLY, 0644);

    dup2(fd, 1);
    fflush(stdout);

    execvp(cmnd, &argv[2]);

  }
}