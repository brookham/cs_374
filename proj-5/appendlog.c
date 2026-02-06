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
  int fd = open("data.dat", O_RDWR|O_CREAT|O_TRUNC, 0666);
  ftruncate(fd, LENGTH);

  void *data = mmap(NULL, LENGTH, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  int *header = data;

  int offset = header[0];
  int count = header[1];

  for (int i = 1; i < argc; i += 2){

    pid_t pid = fork();
    char *prefix = NULL;

    if (pid == 0){
      int *num = ((char *)data + sizeof(int) * 2 + offset);
      *num = atoi(argv[i]);

      prefix = (char *)(num + 1);
      strcpy(prefix, argv[i + 1]);
      offset += 32;
      count += 1;

      header[0] = offset;
      header[1] = count;

    } else {
      printf("%d; %s\n",count, prefix);
      wait(NULL);
    }
  }
}