#include "main.h"

/**
 * process_file_input - Process input from a file.
 * @file: The input file.
 * @alias_names: Array of alias names.
 * @alias_values: Array of alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function reads commands from a file, processes them,
 * and executes them sequentially.
 */
void process_file_input(FILE *file, char *alias_names[],
                        char *alias_values[], int *num_aliases)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = custom_getline(&line, &len, file)) != -1)
    {
        if (line[read - 1] == '\n')
        {
            line[read - 1] = '\0'; /* Remove newline character */
        }

        handle_input(line, alias_names, alias_values, num_aliases);
    }

    free(line);
}
