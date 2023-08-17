#include "main.h"

#define MAX_ALIASES 10
int num_aliases = 0;
char *alias_names[MAX_ALIASES];
char *alias_values[MAX_ALIASES];

/**
 * main - Entry point for the simple shell program.
 *
 * Description:
 * This function implements a basic shell that displays a prompt,
 * reads user input, and executes the entered commands using execve.
 * It continues to display the prompt and wait for user input until
 * the user enters Ctrl+D (EOF).
 *
 * Return: Always returns EXIT_SUCCESS.
 */
int main(void)
{
    char *command;
    size_t bufsize = MAX_COMMAND_LENGTH;

    command = (char *)malloc(bufsize * sizeof(char));
    if (command == NULL)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("#cisfun$ ");
        getline(&command, &bufsize, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (feof(stdin))
        {
            printf("\n");
            break;
        }

        handle_input(command);
    }

    free(command);
    return (EXIT_SUCCESS);
}

/**
 * handle_input - Process the user input and execute commands.
 * @input: The user input.
 *
 * Description:
 * This function splits the input into multiple commands (separated by ;),
 * and then executes each command sequentially using execute_commands.
 */
void handle_input(char *input)
{
    char *commands[MAX_ARGS];  /* Array to store individual commands */
    char *token = strtok(input, ";");

    int i = 0;
    int j;

    while (token != NULL)
    {
        commands[i] = token;
        i++;
        token = strtok(NULL, ";");
    }
    commands[i] = NULL;

    for (j = 0; j < i; j++)
    {
        char *cmd = commands[j];
        execute_commands(cmd);
    }
}

/**
 * execute_commands - Execute a single or multiple commands.
 * @cmd: The command(s) to execute.
 *
 * Description:
 * This function tokenizes the input command(s) using space as the delimiter,
 * then checks and handles built-in commands (exit, env, cd, alias),
 * and finally executes other commands using search_and_execute.
 */
void execute_commands(char *cmd)
{
    char *args[MAX_ARGS];
    split_input(cmd, args);

    if (strcmp(args[0], "exit") == 0)
    {
        handle_exit(args[1]);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        print_environment();
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        handle_cd(args);
    }
    else if (strcmp(args[0], "alias") == 0)
    {
        handle_alias(args);
    }
    else
    {
        replace_variables(args);
        search_and_execute(args);
    }
}

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


/**
 * replace_variables - Replace $ variables in command arguments.
 * @args: The arguments to process for variable replacement.
 *
 * Description:
 * This function replaces $ variables (e.g., $HOME, $$) in the
 * command arguments with their corresponding values.
 */
void replace_variables(char *args[])
{
    int i;
    for (i = 0; args[i] != NULL; i++)
    {
        char *arg = args[i];

        /* Replace $$ with the process ID */
        if (strcmp(arg, "$$") == 0)
        {
            char pid_str[16]; /* Maximum PID length is 5 digits */
            snprintf(pid_str, sizeof(pid_str), "%d", getpid());
            args[i] = strdup(pid_str);
        }
        /* Replace $ variables (e.g., $HOME) */
        else if (arg[0] == '$')
        {
            char *var_name = &arg[1];
            char *var_value = getenv(var_name);
            if (var_value != NULL)
            {
                args[i] = strdup(var_value);
            }
        }
    }
}
