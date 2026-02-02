#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define DATA_SIZE 1024

int main(char *argv[])
{

  int fd = open("data.dat", O_RDONLY);

  void *data = mmap(NULL, DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);

  int *i = data;
  *i = atoi(argv[1]);
  *(i+1) = atof(argv[2]);

  float *j = (float *)(i+1);



  strcpy(*i, data);
  strcpy(j, data);

  munmap(data, sizeof(i) + sizeof(j));

}