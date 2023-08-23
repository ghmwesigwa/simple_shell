#include "main.h"

#define MAX_PROMPT_LENGTH 100

/**
 * process_user_input - Process user input from stdin.
 * @alias_names: Array of alias names.
 * @alias_values: Array of alias values.
 * @num_aliases: Pointer to the number of existing aliases.
 *
 * Description:
 * This function displays a prompt, reads user input, and
 * executes the entered commands.
 */
void process_user_input(char *alias_names[], char *alias_values[], int *num_aliases)
{
    char *command;
    size_t bufsize = MAX_COMMAND_LENGTH;
    char prompt[MAX_PROMPT_LENGTH];

    char *current_dir = NULL;  /* Move this variable declaration to the beginning */

    command = (char *)malloc(bufsize * sizeof(char));
    if (command == NULL)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    current_dir = getcwd(current_dir, MAX_PROMPT_LENGTH);
    if (current_dir == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    generate_prompt_string(prompt, current_dir);

    while (1)
    {
        printf("%s ", prompt);
        getline(&command, &bufsize, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (feof(stdin))
        {
            printf("\n");
            break;
        }
        handle_input(command, alias_names, alias_values, num_aliases);
    }

    free(current_dir);
    free(command);
}

