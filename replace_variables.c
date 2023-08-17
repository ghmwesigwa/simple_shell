#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * replace_variables - Replace variable placeholders with their values.
 * @args: The array of command-line arguments.
 *
 * Description:
 * This function iterates through the array of arguments and replaces
 * any variables of the form "$VAR" with their corresponding values
 * from the environment. The replaced values are then updated in the
 * same arguments array.
 */
void replace_variables(char *args[])
{
    int i;

    for (i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] == '$')
        {
            char *var_name = args[i] + 1; /* Skip the $ */
            char *var_value = getenv(var_name);

            if (var_value != NULL)
            {
                args[i] = var_value;
            }
        }
    }
}
