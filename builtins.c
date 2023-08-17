#include <stdlib.h>
#include "builtins.h"
#include "main.h"

/**
 * handle_exit - Handle the built-in exit command.
 * @status: The exit status (optional).
 *
 * Description:
 * This function handles the exit command, allowing the user to
 * specify an exit status. If no status is provided, it exits
 * with EXIT_SUCCESS.
 */
void handle_exit(char *status)
{
    if (status != NULL)
    {
        int exit_status = atoi(status);
        exit(exit_status);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

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
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}


/**
 * handle_cd - Handle the built-in cd (change directory) command.
 * @args: The arguments passed to the cd command.
 *
 * Description:
 * This function changes the current working directory. If no
 * argument is provided, it changes to the user's home directory.
 */
void handle_cd(char *args[])
{
    if (args[1] == NULL)
    {
        chdir(getenv("HOME"));
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
    setenv("PWD", getcwd(NULL, 0), 1);
}

/**
 * Handle the 'alias' built-in command.
 *
 * This function allows the user to manage aliases, which are custom command
 * shortcuts.
 *
 * @param args          The array of command-line arguments.
 * @param alias_names   An array of existing alias names.
 * @param alias_values  An array of existing alias values.
 * @param num_aliases   A pointer to the number of existing aliases.
 */
void handle_alias(char *args[], char *alias_names[], char *alias_values[], int *num_aliases) {
    if (args[1] == NULL) {
        // Print all aliases
        for (int i = 0; i < *num_aliases; i++) {
            printf("%s='%s'\n", alias_names[i], alias_values[i]);
        }
    } else if (args[2] == NULL) {
        // Print specific alias
        int index = find_alias_index(args[1], num_aliases, alias_names, alias_values);
        if (index != -1) {
            printf("%s='%s'\n", alias_names[index], alias_values[index]);
        } else {
            fprintf(stderr, "Alias not found: %s\n", args[1]);
        }
    } else {
        // Add or update alias
        int index = find_alias_index(args[1], num_aliases, alias_names, alias_values);
        if (index != -1) {
            // Update existing alias
            free(alias_values[index]);
            alias_values[index] = strdup(args[2]);
        } else if (*num_aliases < MAX_ALIASES) {
            // Add new alias
            alias_names[*num_aliases] = strdup(args[1]);
            alias_values[*num_aliases] = strdup(args[2]);
            (*num_aliases)++;
        } else {
            fprintf(stderr, "Maximum number of aliases reached.\n");
        }
    }
}   

/**
 * find_alias_index - Find the index of an alias by name.
 * @name: The alias name to search for.
 *
 * Return: The index of the alias in the arrays, or -1 if not found.
 */
int find_alias_index(const char *name)
{
    int i;
    for (i = 0; i < *num_aliases; i++) {
        if (strcmp(alias_names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

