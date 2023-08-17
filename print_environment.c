#include <stdio.h>
#include <stdlib.h>

/**
 * print_environment - Print the current environment variables.
 *
 * Description:
 * This function displays the current environment
 * variables to the standard output,
 * each on a separate line. It accesses
 * environment variables using the `environ`
 * global variable.
 */
void print_environment(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}

