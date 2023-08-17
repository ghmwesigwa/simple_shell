#include <stdio.h>
#include <stdlib.h>

/**
 * print_environment - Print the current environment variables.
 *
 * Description:
 * This function displays the current environment variables to the standard output,
 * each on a separate line. The environment variables are retrieved using the
 * `extern char **environ` variable, which is an array of strings containing
 * key-value pairs in the format "key=value". The function iterates through the
 * array and prints each environment variable followed by a newline.
 */
void print_environment(void)
{
    extern char **environ;

    int i;
    
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}
