#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define DATA_SIZE 1024

int main(int argc, char *argv[])
{

  //open file for read/write
  int fd = open("data.dat", O_RDWR);
  //map file into memory
  void *data = mmap(NULL, DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  //put int at the start of the mapping
  int *i = (int *)data;
  *i = atoi(argv[1]);

  //place float right after int
  float *f = (float *)(i + 1);
  *f = strtof(argv[2], NULL);

  //place string right after float
  char *s = (char *)(f + 1);
  strcpy(s, argv[3]);

  munmap(data, DATA_SIZE);

  close(fd);

}