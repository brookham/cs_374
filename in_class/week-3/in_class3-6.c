#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{

    char c[1024];
    // Define the tokens array
    char *tokens[128] = {0};

    // TODO: modify tokenize2.c's code to store the tokens in the
    // tokens array (but don't print them)

    printf("prompt> ");
    fflush(stdout);

    fgets(c, sizeof c, stdin);

    char *token;
    int word_count = 0;

    if((token = strtok(c, " \n")) != NULL) do {
        tokens[word_count++] = token;
    } while ((token = strtok(NULL, " \n")) != NULL);

        execvp(tokens[0], tokens);

}