#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("And...\n");

    pid_t pid = fork();

    if (pid == 0){
      execlp("ls", "ls", "-1", NULL);
    } else{
      printf("im the parent\n");
      wait(NULL);
    }

    printf("here we go!\n");
}
