#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 64
#define MAX_COMMAND_LENGTH 1024

extern char **environ;

/* main.c */
void handle_input(char *input);

/* shell.c */
void search_and_execute(char *args[]);
void split_input(char *command, char *args[]);
void execute_command(char *args[]);
void print_environment(void);
<<<<<<< Updated upstream
=======
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
>>>>>>> Stashed changes

#endif /* MAIN_H */

