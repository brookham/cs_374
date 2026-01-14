#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
  DIR* dir_point = opendir("/");

  struct dirent *d = readdir(dir_point);
  printf("%s\n", d->d_name);
  
  while (d->d_name != NULL){
    struct dirent *d = readdir(dir_point);
    printf("%s\n", d->d_name);
  }

  closedir(dir_point);

}