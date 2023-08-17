#include "main.h"
#include "builtins.h"

#define MAX_ALIASES 10
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
	int num_aliases = 0;
	char *alias_names[MAX_ALIASES];
	char *alias_values[MAX_ALIASES];
	
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
void handle_input(command, alias_names, alias_values, &num_aliases)
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

