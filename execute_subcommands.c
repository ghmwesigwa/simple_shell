#include "main.h"

/**
 * execute_subcommands - Execute subcommands using execvp.
 * @args: The arguments to the subcommand.
 *
 * Description:
 * This function executes a sequence of subcommands using execvp.
 */
void execute_subcommands(char *args[]) {
    int status;
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        execute_child(args);
    } else {
        waitpid(child_pid, &status, 0);
    }
}
