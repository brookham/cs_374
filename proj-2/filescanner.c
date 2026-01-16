#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>


//recursive function
// int dir_size(struct dirent *d)
// {
//   struct stat sb;
//   if (S_ISDIR(sb.st_mode)){

//   }

// }


//read dir function
void expand(DIR* dir, char* parent_path)
{
  struct stat sb;
  struct dirent *d  = readdir(dir);

  int dir_size = 0;

  char full_path[256];

  while (d != NULL){
    d = readdir(dir);
    
    if (d == NULL){
      break;
    }

    if ((strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..")) == 0){
      continue;
    }

    sprintf(full_path, "%s/%s", parent_path, d->d_name);

    if (stat(full_path, &sb) == 0){
      dir_size = dir_size + sb.st_size;

    }

    if (S_ISDIR(sb.st_mode)){
      DIR* new_dir = opendir(full_path);
      
      expand(new_dir, full_path);
   
    }

  }
  
  closedir(dir);
  printf("%s: %d\n", full_path, dir_size);

}



int main(int argc, char* argv[])
{
  DIR* dirpoint;
  if (argc == 1){
    dirpoint = opendir(".");
    expand(dirpoint, ".");
  } else if (argc > 2){
    return 1;
  } else {
    dirpoint = opendir(argv[1]);
    expand(dirpoint, argv[1]);
  }
  
  
}




