#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMND_LINE 2048
#define MAX_CMND 128

int internal_cmnd(char *tokens[])
{

  if (strcmp(tokens[0], "cd") == 0)
  {
    int cd = chdir(tokens[1]);
    if (cd == -1)
    {
      perror("cause of problem:");
    }
    else
    {
      return cd;
    }
  }
  if (strcmp(tokens[0], "exit") == 0)
  {
    exit(0);
  }

  return 0;
}

int main(void)
{

  char c[MAX_CMND_LINE];

  char *tokens[MAX_CMND] = {0};

  while (1)
  {

    printf("prompt> ");
    fflush(stdout);
    fgets(c, sizeof c, stdin);

    char *token;
    int word_count = 0;

    if ((token = strtok(c, " \n")) != NULL)
      do
      {

        tokens[word_count++] = token;
      }

      while ((token = strtok(NULL, " \n")) != NULL);

    if (strcmp(tokens[0], "cd") == 0 || strcmp(tokens[0], "exit") == 0)
    {

      internal_cmnd(tokens);
      continue;
    }

    pid_t pid = fork();

    if (pid == 0)
    {

      if (execvp(tokens[0], tokens) == -1)
      {
        perror("exec");
        exit(1);
      }
      else
      {

        execvp(tokens[0], tokens);
      }
    }
    else
    {

      wait(NULL);
    }
  }
  exit(0);
}