#include "main.h"

/**
 * handle_logical_and - Execute a command and handle logical AND operator (&&).
 * @args: The arguments to the command.
 *
 * Description:
 * This function executes a command using execvp and waits for the command to
 * complete. If the command exits with a non-zero status, the remaining commands
 * in the logical AND sequence are skipped.
 */
void handle_logical_and(char *args[]) {
    int status;
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "./shell: ");
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            /* The command in the sequence failed, skip the remaining commands */
            exit(EXIT_FAILURE); /* Terminate the child process with a non-zero status */
        }
    }
}

