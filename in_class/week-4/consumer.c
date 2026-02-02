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
    unsigned char msg_num;
    char buf[16];
    int num, fd;

    mkfifo("./producer", 0644);

    printf("waiting for writers...\n");
    fd = open("./producer", O_RDONLY);

    while (1) {
        num = read(fd, &msg_num, 1);
        if (num == -1) {
            perror("read");
            break;
        } else if (num == 0) {
            break;
        } else {
            sprintf(buf, "%u: Message #%u\n", msg_num, msg_num);
            printf("%s", buf);
        }
    }

    close(fd);
    return 0;
}