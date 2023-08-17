#ifndef MAIN_H
#define MAIN_H

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
void print_environment(char *alias_names[], char *alias_values[], int *num_aliases);
void handle_exit(char *status);
void handle_cd(char *args[]);
void handle_alias(char *args[], char *alias_names[], char *alias_values[], int *num_aliases);
void replace_variables(char *args[]);
void search_and_execute(char *args[]);
int find_alias_index(const char *name);

/* shell.c */
void search_and_execute(char *args[]);
void split_input(char *command, char *args[]);
void execute_command(char *args[]);
void print_environment(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif /* MAIN_H */

