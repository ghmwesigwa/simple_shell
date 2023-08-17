#include "main.h"

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
<<<<<<< Updated upstream
=======
 * This function splits the input into arguments, handles built-in
 * commands (exit and env), and executes other commands using execve.
>>>>>>> Stashed changes
 */
void handle_input(char *input)
{
	char *args[MAX_ARGS];

	split_input(input, args);

	if (strcmp(args[0], "exit") == 0)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_environment();
	}
	else
	{
		search_and_execute(args);
	}
}

