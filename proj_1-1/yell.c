#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

void to_upper(char* buf, int bytes){
  for (int i = 0; i < bytes; i++){
    buf[i] = toupper((char)buf[i]);
  }
}

int main(int argc, char* argv[]){

  int num_files = argc;

  if (num_files == 1){
    char buf[14];

    int bytes_read = 1;

    while (bytes_read != 0){
      bytes_read = read(0, buf, 14);
      to_upper(buf, bytes_read);
      write(1, buf, bytes_read);
    }

  } else {
    int i;

    for (i = 1; i < num_files; i++){
      int fd = open(argv[i], O_RDONLY, 0600);

      char buf[2048];

      int bytes_read = 1;

      while (bytes_read != 0){
        bytes_read = read(fd, buf, 2048);
        to_upper(buf, bytes_read);
        write(1, buf, bytes_read);
      }
      close(fd);
    }

  }
  
}