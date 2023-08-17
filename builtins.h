#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 64

void handle_exit(char *status);
void print_environment(void);
void handle_cd(char *args[]);
void handle_alias(char *args[], char *alias_names[], char *alias_values[]);
int find_alias_index(const char *name);

#endif /* BUILTINS_H */

