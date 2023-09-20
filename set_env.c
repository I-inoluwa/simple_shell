#include "main.h"

/**
 * _setenv - function that sets an environment variable;
 * @name: name of variable to be set;
 * @value: value to be set to (a string);
 * @overwrite: value that specifies if variable should be overwritten;
 * Return: returns exit status;
 */

int _setenv(char *name, char *value, int overwrite)
{
	char *new, **arr;

	size_t i;

	if (name == NULL || value == NULL)
		return (2);

	new = join_strs(name, value, "=");
	for (i = 0; envpath[i] != NULL; i++)
	{
		arr = split_str(envpath[i], "=");
		if (match_command(arr[0], name))
		{
			if (overwrite != 0)
			{
				free(envpath[i]);
				envpath[i] = _strdup(new);
				free(new);
				free_arr(arr);
				return (0);
			}
		}
		free_arr(arr);
	}
	envpath = str_to_arr(new, envpath);
	free(new);

	return (0);
}

/**
 * _unsetenv - function to clear an environment variable;
 * @name: name of variable to be cleared;
 * Return: exit status;
 */

int _unsetenv(char *name)
{
	char **arr = NULL;

	size_t i, j, len = array_len(envpath);

	if (name == NULL)
		return (2);

	for (i = 0; i < len; i++)
	{
		arr = split_str(envpath[i], "=");
		if (match_command(name, "xstat"))
		{
			free_arr(arr);
			return (2);
		}
		if (match_command(arr[0], name))
		{
			free_arr(arr);
			for (j = i; j < len - 1; j++)
			{
				free(envpath[j]);
				envpath[j] = _strdup(envpath[j + 1]);
			}
			free(envpath[j]);
			envpath[j] = NULL;

			return (0);
		}
		free_arr(arr);
	}

	return (2);
}

/**
 * _getenv - function that gets the value of an environment variable;
 * @variable: name of variable;
 * Return: the string value of the variable;
 */

char *_getenv(char *variable)
{
	size_t ind;
	char **arr = NULL, *value = NULL;

	if (variable == NULL)
		return (NULL);

	for (ind = 0; envpath[ind] != NULL; ind++)
	{
		arr = split_str(envpath[ind], "=");
		if (match_command(arr[0], variable))
		{
			value = _strdup(arr[1]);
			free_arr(arr);
			return (value);
		}
		free_arr(arr);
	}

	return (NULL);
}

/**
 * handle_unsetenv - handles the unsetenv builtin command;
 * @args: array of CLI arguments;
 * Return: Exit status;
 */

int handle_unsetenv(char *args[])
{
	int xstat = 0;

	if (array_len(args) != 2)
	{
		/*_print("Syntax: unsetenv VARIABLE");*/
		return (2);
	}

	xstat = _unsetenv(args[1]);
	/*if (xstat == 2)*/
	/*	_print("Unsetenv function call FAILED");*/

	return (xstat);
}
