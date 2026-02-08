#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define LENGTH (sizeof(int) * 2 + 1048576 * 32)

int main(int argc, char *argv[])
{
  struct flock lock = {
      .l_type = F_WRLCK,
      .l_whence = SEEK_SET,
      .l_start = 0,
      .l_len = 0

  };
  int fd = open("data.dat", O_RDWR | O_CREAT | O_TRUNC, 0666);

  ftruncate(fd, LENGTH);

  void *data = mmap(NULL, LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int *header = data;
  header[0] = 0;
  header[1] = 0;

  for (int i = 1; i + 1 < argc; i += 2)
  {

    pid_t pid = fork();

    if (pid == 0)
    {
      lock.l_type = F_WRLCK;
      fcntl(fd, F_SETLKW, &lock);
      for (int j = 0; j < atoi(argv[i]); j++)
      {

        char *log = (char *)data + sizeof(int) * 2 + header[0];
        snprintf(log, 32, "%d: %s", header[1], argv[i + 1]);


        header[0] += 32;
        header[1] += 1;
      }
      lock.l_type = F_UNLCK;
      fcntl(fd, F_SETLKW, &lock);
      _exit(0);
    }
    else
    {

      wait(NULL);
    }
    printf("%.*s", header[0], (char *)data + sizeof(int) * 2);
    munmap(data, LENGTH);
    close(fd);
  }
}