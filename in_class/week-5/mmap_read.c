#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define DATA_SIZE 1024

int main()
{

  int fd = open("data.dat", O_RDONLY);

  void *data = mmap(NULL, DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);

  //first bytes as int
  int *i = (int *)data;
  //float start right after int
  float *f = (float *)(i + 1);
  //string starts right after float
  char *s = (char *)(f + 1);

  printf("%d\n", *i);
  printf("%f\n", *f);
  printf("%s\n", s);



  munmap(data, DATA_SIZE);
  close(fd);

}