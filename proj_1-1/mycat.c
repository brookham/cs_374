#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  int num_files = argc;

  if (num_files == 1){
    char buf[14];

    int bytes_read = 1;

    while (bytes_read != 0){
      bytes_read = read(0, buf, 14);
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

        write(1, buf, bytes_read);
      }
      close(fd);
    }

  }
  
}