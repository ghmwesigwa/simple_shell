#include "main.h"


/**
 * search_and_execute - Execute the given command using execve.
 * @args: The arguments to the command.
 *
 * Description:
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
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

}

