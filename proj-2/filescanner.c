#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>

#define MAX_SIZE 4096
#define MIN_SIZE 0

long long expand(DIR* dir, char* parent_path)
{

  if (dir == NULL) {
    return 0;
  }

  struct stat sb;
  struct dirent *d;

  long long dir_size = MIN_SIZE;

  char full_path[MAX_SIZE];

  while ((d = readdir(dir)) != NULL){

    if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0){
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", parent_path, d->d_name);

    if (lstat(full_path, &sb) == 0){
      
      if (S_ISDIR(sb.st_mode)){
        DIR* new_dir = opendir(full_path);
        if (new_dir != NULL){
          long long subdir_size = expand(new_dir, full_path);
          dir_size = dir_size + subdir_size;
        }

      } else {
        dir_size = dir_size + sb.st_size;
      }
    }

  }
  
  closedir(dir);
  printf("%s: %lld\n", parent_path, dir_size);
  return dir_size;

}

void print_usage(char* program_name) {
  fprintf(stderr, "Usage: %s [directory]\n", program_name);
  fprintf(stderr, "  If no directory is provided, scans current directory.\n");
}

int main(int argc, char* argv[])
{

  DIR* dirpoint;

  if (argc == 1){
    dirpoint = opendir(".");
    expand(dirpoint, ".");
  } 
  
  else if (argc > 2){
    print_usage(argv[0]);
    return 1;
  } 
  
  else {
    dirpoint = opendir(argv[1]);
    if (dirpoint == NULL){
      perror("opendir");
      print_usage(argv[0]);
      return 1;
    }
    expand(dirpoint, argv[1]);
  }
}




