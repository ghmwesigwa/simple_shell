#include "main.h"

/**
 * execute_command - Execute the given command using execve.
 * @command: The command to execute.
 *
 * Description:
 * This function forks a child process and uses execve to
 * execute the specified command. It waits for the child
 * process to complete if it's the parent process.
 */
void execute_command(char *command)
{
	extern char **environ; /* Declare environ variable */
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		char *args[MAX_ARGS];
		char *token = strtok(command, " "); /* Split command into tokens */

		int i = 0;

		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;/* Null-terminate the array */

		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: ", args[0]);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

