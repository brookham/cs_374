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

    fd = open("./producer", O_WRONLY);

    if (argc > 2){
      perror("wrong");
    }else{
      int limit = atoi(argv[1]);
      int count;
      while (count < limit) {
        printf("sending %d, message#%d", count, count);
      }
    }

    write(fd, argv[1], 16);
    sleep(1);
    close(fd);
}