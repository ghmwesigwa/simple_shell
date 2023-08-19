#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * handle_cd - Handle the built-in cd (change directory) command.
 * @args: The arguments passed to the cd command.
 *
 * Description:
 * This function changes the current working directory. If no
 * argument is provided, it changes to the user's home directory.
 */
void handle_cd(char *args[])
{
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
}

