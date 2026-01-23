#include <stdio.h>
#include <string.h>

int main(void){

  char c[1024];

  fgets(c, sizeof c, stdin);

  char *token;

  int word_count = 0;

  if ((token = strtok(c, " \n" )) != NULL) do
      printf("%d: %s\n", word_count++, token);
      
  while ((token = strtok(NULL, " \n")) != NULL);
}