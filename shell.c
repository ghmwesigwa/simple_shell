#include "main.h"


/**
 * search_and_execute - Execute the given command using execve.
 * @args: The arguments to the command.
 *
 * Description:
 *     This function forks a child process and uses execve to
 *     execute the specified command. It waits for the child
 *     process to complete if it's the parent process.
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
 * split_input - Split the user command into arguments.
 * @command: The user command.
 * @args: The array to store the arguments.
 *
 * Description:
 *     This function tokenizes the user command using space as the delimiter
 *     and stores the resulting arguments in the provided array.
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
	args[i] = NULL;
}

/**
 * print_environment - Print the current environment variables.
 *
 * Description:
 *     This function prints the current environment variables line by line.
 */
void print_environment(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

