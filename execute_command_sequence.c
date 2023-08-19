#include "main.h"

/**
 * execute_command_sequence - Execute a sequence of commands using execve.
 * @commands: The array of commands.
 *
 * Description:
 * This function executes a sequence of commands in the array using execve.
 * It handles command separators (;) and shell logical operators (&&, ||).
 */
void execute_command_sequence(char *commands[])
{
    int i = 0;
    char *temp_args[MAX_ARGS];

    while (commands[i] != NULL) {
        if (strcmp(commands[i], ";") == 0 || strcmp(commands[i], "&&") == 0 || strcmp(commands[i], "||") == 0) {
            commands[i] = NULL; /* Terminate the current command */

            /* Copy elements to temp_args */
            int j = 0;
            for (int k = i + 1; commands[k] != NULL; k++) {
                temp_args[j++] = commands[k];
            }
            temp_args[j] = NULL;

            execute_subcommand(temp_args);

            i++;
        } else {
            temp_args[i] = commands[i];
            i++;
        }
    }
}
