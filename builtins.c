#include <stdio.h>
#include <string.h>
#include "builtins.h"

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

    int i;
    
    for (i = 0; environ[i] != NULL; i++)
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
 * handle_alias - Handle the 'alias' built-in command.
 * @args: The array of command-line arguments.
 * @alias_names: An array of existing alias names.
 * @alias_values: An array of existing alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function allows the user to manage aliases, which are custom command shortcuts.
 */
void handle_alias(char *args[], char *alias_names[], char *alias_values[], int *num_aliases)
{
    if (args[1] == NULL)
    {
        /*  Print all aliases */
        int i;
	
	for (i = 0; i < *num_aliases; i++)
        {
            printf("%s='%s'\n", alias_names[i], alias_values[i]);
        }
    }
    else if (args[2] == NULL)
    {
        /* Print specific alias */
        int index = find_alias_index(args[1], alias_names, *num_aliases);

        if (index != -1)
        {
            printf("%s='%s'\n", alias_names[index], alias_values[index]);
        }
        else
        {
            fprintf(stderr, "Alias not found: %s\n", args[1]);
        }
    }
    else
    {
        /* Add or update alias */
        int index = find_alias_index(args[1], alias_names, *num_aliases);

        if (index != -1)
        {
            /* Update existing alias */
            free(alias_values[index]);
            alias_values[index] = strdup(args[2]);
        }
        else if (*num_aliases < MAX_ALIASES)
        {
            /* Add new alias */
            alias_names[*num_aliases] = strdup(args[1]);
            alias_values[*num_aliases] = strdup(args[2]);
            (*num_aliases)++;
        }
        else
        {
            fprintf(stderr, "Maximum number of aliases reached.\n");
        }
    }
}

/**
 * find_alias_index - Find the index of an alias by name.
 * @name: The alias name to search for.
 * @alias_names: An array of alias names.
 * @num_aliases: The number of existing aliases.
 *
 * Return: The index of the alias in the arrays, or -1 if not found.
 */
int find_alias_index(const char *name, char *alias_names[], int num_aliases)
{
    int i;
    
    for (i = 0; i < num_aliases; i++)
    {
        if (strcmp(alias_names[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * replace_variables - Replace variable placeholders with their values.
 * @args: The array of command-line arguments.
 *
 * Description:
 * This function iterates through the array of arguments and replaces
 * any variables of the form "$VAR" with their corresponding values
 * from the environment. The replaced values are then updated in the
 * same arguments array.
 */
void replace_variables(char *args[])
{
    int i;

    for (i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] == '$')
        {
            char *var_name = args[i] + 1; /* Skip the $ */
            char *var_value = getenv(var_name);

            if (var_value != NULL)
            {
                args[i] = var_value;
            }
        }
    }
}
