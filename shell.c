#include "main.h"


/**
 * search_and_execute - Execute the given command using execve.
 * @args: The arguments to the command.
 *
 * Description:
 */
void search_and_execute(char *args[])
<<<<<<< Updated upstream
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
=======
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
 * This function tokenizes the user command using space as the delimiter
 * and stores the resulting arguments in the provided array.
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
 * execute_command - Execute the given command using execve.
 * @args: The arguments to the command.
 *
 * Description:
 * This function is responsible for executing the given command
 * using execve. It also handles built-in commands (exit and env).
 */
void execute_command(char *args[])
{
        if (strcmp(args[0], "exit") == 0)
        {
                free(args);
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

/**
 * print_environment - Print the current environment variables.
 *
 * Description:
 * This function prints the current environment variables line by line.
 */
void print_environment(void)
{
        int i = 0;

        while (environ[i] != NULL)
        {
                printf("%s\n", environ[i]);
                i++;
        }
}

/**
 * custom_getline - Read a line of input from a stream.
 * @lineptr: A pointer to the buffer storing the line.
 * @n: The size of the buffer.
 * @stream: The input stream to read from (e.g., stdin).
 *
 * Return: The number of characters read, or -1 on failure or EOF.
 *
 * Description:
 * This function reads a line of input from the specified stream,
 * dynamically allocating memory for the line buffer as needed.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
        ssize_t chars_read = getline(lineptr, n, stream);

        if (chars_read == -1)
        {
                return (-1);
        }
        return (chars_read);
>>>>>>> Stashed changes
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

