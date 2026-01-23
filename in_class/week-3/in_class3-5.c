#include <stdio.h>
#include <string.h>

int main(void)
{

    char c[1024];
    // Define the tokens array
    char *tokens[128] = {0};

    // TODO: modify tokenize2.c's code to store the tokens in the
    // tokens array (but don't print them)

    fgets(c, sizeof c, stdin);

    char *token;
    int word_count = 0;

    if((token = strtok(c, " \n")) != NULL) do {
        tokens[word_count++] = token;
    } while ((token = strtok(NULL, " \n")) != NULL);

    // Prints out the tokens
    for (int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);
}