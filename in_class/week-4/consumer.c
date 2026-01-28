#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(void)
{
    char buf[300];

    int num, fd;

    mkfifo("./producer", 0644);

    fd = open("./producer", O_RDONLY);

    while(1){
      if((num = read(fd, buf, 24)) == -1){
        perror("read");
      }
      else{
        if(num > 0){
          printf("read: %s", buf); 
        }
      }
    }
    return 0;
}