#include "main.h"

#define MAX_ALIASES 10
#define MAX_PROMPT_LENGTH 100

/**
 * main - Entry point for the simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * Description:
 * This function implements a basic shell that displays a prompt,
 * reads user input, and executes the entered commands using execve.
 * It continues to display the prompt and wait for user input until
 * the user enters Ctrl+D (EOF).
 *
 * Return: Always returns EXIT_SUCCESS
 */
int main(int argc, char *argv[])
{
	int num_aliases = 0;
	char *alias_names[MAX_ALIASES];
	char *alias_values[MAX_ALIASES];

	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");

		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}

		process_file_input(file, alias_names, alias_values, &num_aliases);
		fclose(file);
	}
	else if (argc == 1)
	{
		process_user_input(alias_names, alias_values, &num_aliases);
	}
	else
	{
		print_usage(argv[0]);
	}

	return (EXIT_SUCCESS);
}

/**
 * handle_input - Process the user input and execute commands.
 * @input: The user input.
 * @alias_names: Array of alias names.
 * @alias_values: Array of alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function splits the input into multiple commands (separated by ;),
 * and then executes each command sequentially using execute_commands.
 */
void handle_input(char *input, char *alias_names[],
                  char *alias_values[], int *num_aliases)
{
	char *commands[MAX_ARGS]; /* Array to store individual commands */
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

		execute_commands(cmd, alias_names, alias_values, num_aliases);
	}
}

/**
 * execute_commands - Execute a single or multiple commands.
 * @cmd: The command(s) to execute.
 * @alias_names: Array of alias names.
 * @alias_values: Array of alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function tokenizes the input command(s) using space as the delimiter,
 * then checks and handles built-in commands (exit, env, cd, alias),
 * and finally executes other commands using search_and_execute.
 */
void execute_commands(char *cmd, char *alias_names[],
                      char *alias_values[], int *num_aliases)
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
		handle_alias(args, alias_names, alias_values, num_aliases);
	}
	else
	{
		replace_variables(args);
		search_and_execute(args);
	}
}

