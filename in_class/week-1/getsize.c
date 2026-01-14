#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
  if (argc == 1){
    struct stat buf;
    stat(argv[1], &buf);
    printf("%s: %d", argv[1], buf.st_size);
  } else {
    for (int i = 1; i < argc; i++){
      struct stat buf;
      stat(argv[i], &buf);
      printf("%s: %d\n",argv[i], buf.st_size);
    }
  }


}