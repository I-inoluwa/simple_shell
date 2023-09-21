#include "main.h"

/**
 * get_path - gets the path of a command;
 * @command: string argument;
 * Return: the command, if the command is already a valid path, otherwise:
 * the path to the command, or (NULL) on failure..
 */

char *get_path(char *command)
{
	char *path = NULL;
	char **paths = NULL;
	int ind;
	struct stat sbuf;

	if (stat(command, &sbuf) == 0 && count_in_str('/', command, ""))
	{
		path = _strdup(command);
		return (path);
	}

	path = _getenv("PATH");
	if (path == NULL || match_command(path, ""))
		return (NULL);

	paths = split_str(path, ":");
	free(path);

	for (ind = 0; paths[ind] != NULL; ind++)
	{
		path = join_strs(paths[ind], command, "/");

		if (stat(path, &sbuf) == 0)
		{
			free_arr(paths);
			return (path);
		}
		free(path);
	}
	free_arr(paths);

	return (NULL);
}
