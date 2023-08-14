#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

extern char **environ;

void execute_command(char *command);
void search_and_execute(char *args[]);
void split_input(char *command, char *args[]);

#endif /* MAIN_H */

