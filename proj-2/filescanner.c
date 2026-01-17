#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>

#define MAX_SIZE 4096
#define MIN_SIZE 0

void expand(DIR* dir, char* parent_path)
{
  struct stat sb;
  struct dirent *d  = readdir(dir);

  long long dir_size = MIN_SIZE;

  char full_path[MAX_SIZE];

  while ((d = readdir(dir)) != NULL){

    if ((strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..")) == 0){
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", parent_path, d->d_name);

    if (stat(full_path, &sb) == 0){
      dir_size = dir_size + sb.st_size;
    }

    if (S_ISDIR(sb.st_mode)){
      DIR* new_dir = opendir(full_path);
      expand(new_dir, full_path);
    }
  }
  
  closedir(dir);
  printf("%s: %lld\n", parent_path, dir_size);

}

int main(int argc, char* argv[])
{

  DIR* dirpoint;

  if (argc == 1){
    dirpoint = opendir(".");
    expand(dirpoint, ".");
  } 
  
  else if (argc > 2){
    printf("To Many Arguments\n");
    return 1;
  } 
  
  else {
    dirpoint = opendir(argv[1]);
    expand(dirpoint, argv[1]);
  }
}




