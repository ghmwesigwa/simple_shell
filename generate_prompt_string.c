#include "main.h"

#define MAX_PROMPT_LENGTH 100

/**
 * generate_prompt_string - Generate the prompt string.
 * @prompt: The buffer to store the prompt string.
 * @current_dir: The current working directory.
 *
 * Description:
 * This function generates the prompt string to be displayed.
 */
void generate_prompt_string(char *prompt, char *current_dir)
{
	snprintf(prompt, MAX_PROMPT_LENGTH, "#cisfun:%s$", current_dir);
}

