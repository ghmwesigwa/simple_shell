#include "main.h"
/**
 * execute_subcommand - Execute a subcommand using execve.
 * @sub_args: The arguments of the subcommand.
 *
 * Description:
 * This function forks a child process and uses execve to execute a subcommand.
 * It waits for the child process to complete if it's the parent process.
 */
void execute_subcommand(char *sub_args[])
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        if (execvp(sub_args[0], sub_args) == -1) {
            fprintf(stderr, "./shell: ");
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &status, 0);
    }
}
