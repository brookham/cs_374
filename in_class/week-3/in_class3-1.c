#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    printf("And...\n");

    pid_t pid = fork();

    if (pid == 0){

      printf("im the child\n");
    } else{
      printf("im the parent\n");
    }

    printf("here we go!\n");
}