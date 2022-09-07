#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* function prototypes */
/* ---------------String functions-------------------*/

char *_strcat(char *dst, char *src);
int _strcmp(char *, char *);
int _strlen(char *);
char *_strdup(char *s);
char *_strndup(char *s, int n);

/* ================================================== */

#endif
