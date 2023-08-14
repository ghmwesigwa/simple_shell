#include "main.h"

/**
 * search_and_execute - Search for and execute the specified command.
 * @args: An array of strings containing the command and its arguments.
 */
void search_and_execute(char *args[])
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* Execute the command with full path */
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "./shell: ");
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * split_input - Split the input command into an array of arguments.
 * @command: The command string to be split.
 * @args: An array of strings to store the arguments.
 */
void split_input(char *command, char *args[])
{
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL; /* Null-terminate the array */
}

