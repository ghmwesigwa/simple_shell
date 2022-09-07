#include "shell.h"

/**
 * free_double_ptr - free malloced arrays
 * @s: array of strings
 */
void free_double_ptr(char **s)
{
	int i = 0;

	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
