#include "main.h"

/**
 * print_usage - Print the usage message.
 * @program_name: The name of the program.
 *
 * Description:
 * This function prints the correct usage of the program.
 */
void print_usage(char *program_name)
{
	fprintf(stderr, "Usage: %s [filename]\n", program_name);
	exit(EXIT_FAILURE);
}

