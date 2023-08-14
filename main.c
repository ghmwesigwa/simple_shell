#include "main.h"

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
	char *args[MAX_ARGS];

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

		split_input(command, args);
		search_and_execute(args);
	}

	free(command);
	return (EXIT_SUCCESS);
}

