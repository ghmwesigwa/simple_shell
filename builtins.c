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
 * handle_alias - Handle the built-in alias command.
 * @args: The arguments passed to the alias command.
 *
 * Description:
 * This function allows the user to create, update, or display aliases.
 */
void handle_alias(char *args[])
{
    if (args[1] == NULL)
    {
        int i;

	/* Print list of aliases */
        for (i = 0; i < num_aliases; i++)
        {
            printf("%s='%s'\n", alias_names[i], alias_values[i]);
        }
    }
    else
    {
        /* Create or update alias */
        char *alias_name = strtok(args[1], "=");
        char *alias_value = strtok(NULL, "=");

        if (alias_name != NULL && alias_value != NULL)
        {
            int index = find_alias_index(alias_name);

            if (index != -1)
            {
                /* Update existing alias */
                free(alias_values[index]);
                alias_values[index] = strdup(alias_value);
            }
            else
            {
                /* Create new alias */
                if (num_aliases < MAX_ALIASES)
                {
                    alias_names[num_aliases] = strdup(alias_name);
                    alias_values[num_aliases] = strdup(alias_value);
                    num_aliases++;
                }
                else
                {
                    fprintf(stderr, "Alias limit reached\n");
                }
            }
        }
        else
        {
            fprintf(stderr, "Invalid alias syntax: alias name='value'\n");
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
    for (i = 0; i < num_aliases; i++)
    {
        if (strcmp(alias_names[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

