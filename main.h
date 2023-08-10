#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

/* main.c */
int main(void);

/* shell.c */
void execute_command(char *command);

#endif /* MAIN_H */

