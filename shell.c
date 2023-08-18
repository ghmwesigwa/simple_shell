#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <ctype.h>


/**
 * trim_whitespace - Remove leading and trailing whitespace from a string.
 * @str: The string to trim.
 *
 * Return: A pointer to the trimmed string.
 *
 * Description:
 * This function removes any leading and trailing whitespace characters
 * (spaces, tabs, etc.) from the given string.
 */
char *trim_whitespace(char *str)
{
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}


/**
 * search_and_execute - Execute the given command using execve.
 * @args: The arguments to the command.
 *
 * Description:
 * This function forks a child process and uses execve to execute the specified
 * command. It waits for the child process to complete if it's the parent process.
 * Additionally, it handles shell logical operators (&&, ||) and their execution.
 */
void search_and_execute(char *args[]) {
    pid_t child_pid;
    int status;

    int i = 0;
    char *temp_args[MAX_ARGS];

    while (args[i] != NULL) {
        if (strcmp(args[i], ";") == 0 || strcmp(args[i], "&&") == 0 || strcmp(args[i], "||") == 0) {
            args[i] = NULL; /* Terminate the current command */

            /* Copy elements to temp_args */
            int j = 0;
            for (int k = i + 1; args[k] != NULL; k++) {
                temp_args[j++] = args[k];
            }
            temp_args[j] = NULL;

            child_pid = fork();
            if (child_pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (child_pid == 0) {
                if (execvp(temp_args[0], temp_args) == -1) {
                    fprintf(stderr, "./shell: ");
                    perror(NULL);
                    exit(EXIT_FAILURE);
                }
            } else {
                waitpid(child_pid, &status, 0);
            }

            i++;
        } else {
            temp_args[i] = args[i];
            i++;
        }
    }
    temp_args[i] = NULL; /* Terminate the last command */

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        if (execvp(temp_args[0], temp_args) == -1) {
            fprintf(stderr, "./shell: ");
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &status, 0);
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
 * This function is responsible for executing the given command using execve.
 * It also handles built-in commands (exit, env), command separator (;), and
 * shell logical operators (&&, ||).
 */
void execute_command(char *args[])
{
    if (strcmp(args[0], "exit") == 0) {
        free(args);
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "env") == 0) {
        print_environment();
    } else {
        char *token;
        char *command_copy = strdup(args[0]);
        
        /* Split and execute commands separated by ; */
        token = strtok(command_copy, ";");
        while (token != NULL) {
            char *command = trim_whitespace(token);
            char *command_args[MAX_ARGS];
            split_input(command, command_args);
            search_and_execute(command_args);
            token = strtok(NULL, ";");
        }
        free(command_copy);
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
	size_t len = 0;
	int c;

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128; /* Initial buffer size */
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (len + 1 >= *n)
		{
			*n *= 2; /* Double the buffer size */
			*lineptr = (char *)realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[len++] = c;
	}

	if (c == EOF && len == 0)
	{
		return (-1); /* No input read */
	}

	(*lineptr)[len] = '\0';
	return (len);
}
