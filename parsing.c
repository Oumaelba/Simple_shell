#include "shell.h"
/**
 * parse - Tokenizes a string into an array of arguments
 * @str: The string to be tokenized
 * @del: The delimiter used for tokenization
 *
 * Return: An array of strings containing the parsed arguments,
 *         or NULL on failure
 */
char **parse(char *str, char *del)
{
	char **args = NULL;
	int a_i = 0;
	char *to_ken = NULL;
	int len = 0;

	len = length_of_paths(str, del);
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	args[len] = 0;
	to_ken = strtok(str, del);
	while (to_ken)
	{
		args[a_i] = _strdup(to_ken);
		if (!args[a_i])
		{
			free_buff(args);
			return (NULL);
		}
		a_i++;
		to_ken = strtok(NULL, del);
	}
	return (args);
}
