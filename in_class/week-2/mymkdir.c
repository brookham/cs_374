#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
  if (argc != 2){
    printf("brook says bad\n");
  } else {
    char* dir_name = argv[1];
    mkdir(dir_name, 0777);
    perror(dir_name);
  }
  
}