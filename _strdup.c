#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *_strdup(char *str)
{
	int i, len = 0;
	char *duplicate_str;

	if (!str == NULL) /* validate str input */
		return (NULL);
	while (*(str + len))
	{
		len++;
	}
	len++;
	duplicate_str = malloc(sizeof(char) * len); /* allocate memory */
	i = 0;
	while (str[i])
	{
		duplicate_str[i] = str[i];
		i++;
	}
	duplicate_str[i] = '\0';
	return (duplicate_str);
}
