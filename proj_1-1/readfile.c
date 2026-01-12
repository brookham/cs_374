#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  int fd = open(argv[1], O_RDONLY, 0600);
  
  char buf[128];
  int bytes_read = read(fd, buf, 128);

  write(1, buf, bytes_read);

  close(fd);
}