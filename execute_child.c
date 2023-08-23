#include "main.h"

/**
 * execute_child - Execute a command using execvp.
 * @args: The arguments to the command.
 *
 * Description:
 * This function is responsible for executing a command using execvp.
 */
void execute_child(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
		fprintf(stderr, "./shell: ");
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}

