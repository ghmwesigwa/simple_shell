#include "main.h"
#include <errno.h>

/**
 * main - Entry point for the simple shell program.
 *
 * Description:
 *     This function implements a basic shell that displays a prompt,
 *     reads user input, and executes the entered commands using execve.
 *     It continues to display the prompt and wait for user input until
 *     the user enters Ctrl+D (EOF).
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

		/* Read user input */
		getline(&command, &bufsize, stdin);

		/* Remove newline character from the input */
		command[strcspn(command, "\n")] = '\0';

		/* Exit if Ctrl+D (EOF) is encountered */
		if (feof(stdin))
		{
			printf("\n");
			break;
		}

		execute_command(command);
	}

	free(command);
	return (EXIT_SUCCESS);
}

/**
 * execute_command - Execute the given command using execve.
 * @command: The command to execute.
 *
 * Description:
 *     This function forks a child process and uses execve to
 *     execute the specified command. It waits for the child
 *     process to complete if it's the parent process.
 */
#include "main.h"

void execute_command(char *command)
{
	extern char **environ;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, environ) == -1)
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

