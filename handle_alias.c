#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"

/**
 * handle_alias - Handle the 'alias' built-in command.
 * @args: The array of command-line arguments.
 * @alias_names: An array of existing alias names.
 * @alias_values: An array of existing alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function allows the user to manage aliases,
* which are custom command shortcuts.
 */
void handle_alias(char *args[], char *alias_names[], char *alias_values[],
int *num_aliases)
{
	if (args[1] == NULL)
	{
		/* Print all aliases */
		int i;

		for (i = 0; i < *num_aliases; i++)
		{
			printf("%s='%s'\n", alias_names[i], alias_values[i]);
		}
	}
	else if (args[2] == NULL)
	{
		/* Print specific alias */
		int index = find_alias_index(args[1], alias_names, *num_aliases);

		if (index != -1)
		{
			printf("%s='%s'\n", alias_names[index], alias_values[index]);
		}
		else
		{
			fprintf(stderr, "Alias not found: %s\n", args[1]);
		}
	}
	else
	{
		handle_alias_add_update(args, alias_names, alias_values, num_aliases);
	}
}

/**
 * handle_alias_add_update - Add or update an alias.
 * @args: The array of command-line arguments.
 * @alias_names: An array of existing alias names.
 * @alias_values: An array of existing alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function adds or updates an alias based on the provided arguments.
 */
void handle_alias_add_update(char *args[], char *alias_names[],
char *alias_values[], int *num_aliases)
{
	int index = find_alias_index(args[1], alias_names, *num_aliases);

	if (index != -1)
	{
		/* Update existing alias */
		free(alias_values[index]);
		alias_values[index] = strdup(args[2]);
	}
	else if (*num_aliases < MAX_ALIASES)
	{
		/* Add new alias */
		alias_names[*num_aliases] = strdup(args[1]);
		alias_values[*num_aliases] = strdup(args[2]);
		(*num_aliases)++;
	}
	else
	{
		fprintf(stderr, "Maximum number of aliases reached.\n");
	}
}

/**
 * find_alias_index - Find the index of an alias by name.
 * @name: The alias name to search for.
 * @alias_names: An array of alias names.
 * @num_aliases: The number of existing aliases.
 *
 * Return: The index of the alias in the arrays, or -1 if not found.
 */
int find_alias_index(const char *name, char *alias_names[], int num_aliases)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		if (strcmp(alias_names[i], name) == 0)
		{
			return (i);
		}
	}
	return (-1);
}

