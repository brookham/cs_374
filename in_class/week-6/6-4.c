#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigusr1_happened;

void sigusr1_handler(int sig)

{
  (void)sig;
  sigusr1_happened = 1;
  
  
}

int main(void)
{
  struct sigaction sa = {
    .sa_handler = sigusr1_handler,
    .sa_flags = 0,
  };
  printf("Go to another window and `kill -USR1 %d`\n", getpid());
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);
  
  while (sigusr1_happened == 0){
    sleep(10);
  }
  printf("SIGUSR1 happened!\n");

}
//1. because without sleep() you would just be sitting there waiting, 
//   and waising the cpu, while sleep() blocks the process altogehter

//2. the volatile keyword prevents the compiler from doing anything to 
//   objects that can not be controlled by the compiler, i guarantees that
//   it will be atomic