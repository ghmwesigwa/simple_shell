#ifndef MAIN_H
#define MAIN_H

#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define MAX_ALIASES 10

extern char **environ;

/* main.c */
void handle_input(char *input, char *alias_names[], char *alias_values[], int *num_aliases);
void execute_commands(char *cmd, char *alias_names[], char *alias_values[], int *num_aliases); 
void split_input(char *command, char *args[]);
void execute_command(char *args[]);
void replace_variables(char *args[]);
void search_and_execute(char *args[]);

/* shell.c */
void search_and_execute(char *args[]);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif /* MAIN_H */

