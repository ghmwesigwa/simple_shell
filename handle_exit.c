#include <stdlib.h>

/**
 * handle_exit - Handle the built-in exit command.
 * @status: The exit status (optional).
 *
 * Description:
 * This function handles the exit command, allowing the user to
 * specify an exit status. If no status is provided, it exits
 * with EXIT_SUCCESS.
 */
void handle_exit(char *status)
{
    if (status != NULL)
    {
        int exit_status = atoi(status);

        exit(exit_status);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}
