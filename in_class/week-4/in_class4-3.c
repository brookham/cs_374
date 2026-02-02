#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
  int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);

  dup2(fd, 1);
  printf("Hello, world\nThis is a test!\n");
  

  close(fd);
}