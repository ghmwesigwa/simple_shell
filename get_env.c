#include "shell.h"

/**
 * c_strdup - custom string duplication; excludes beginning bytes
 * @str: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @c: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *c_strdup(char *str, int c)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	/* calculate len + null terminator to malloc */
	while (*(str + len))
		len++;
	len++;

	/* allocate memory but exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - c));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - c))
	{
		*(duplicate_str + i) = *(str + c + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * get_env - finds and returns a copy of the requested environmental variable
 * @str: string to store it in
 * @env: entire set of environmental variables
 * Return: copy of requested environmental variable
 */
char *get_env(char *str, list_t *env)
{
	int j = 0, c = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0' && (env->var)[j] == '=')
			break;
		env = env->next;
	}

	while (str[c] != '\0') /* find how many bytes in env variable title */
		c++;
	c++; /*counts 1 more for = sign*/
	return (c_strdup(env->var, c)); /* make a copy of variable w/o title */
}
