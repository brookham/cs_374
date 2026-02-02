#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd;

  mkfifo("./producer", 0644);

  printf("waiting for readers...\n");
  fd = open("./producer", O_WRONLY);

  if (argc != 2)
  {
    perror("wrong");
  }

  int limit = atoi(argv[1]);
  for (int count = 0; count < limit; count++)
  {
    printf("Sending %d Message #%d\n", count, count);
    write(fd, &count, 1);
    sleep(1);
  }

  close(fd);
  return 0;
}