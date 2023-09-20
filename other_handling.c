#include "main.h"

/**
 * handle_asterisks - handles wildcard '*' in  CLI input;
 * @line: CLI input;
 * Return: the expanded string (or returns the original);
 * NOT YET FULLY FUNCTIONAL.
 */

char *handle_asterisks(char *line)
{
	size_t ind = 0;
	char **files = NULL, **matched = NULL, *match = NULL;

	if (line == NULL)
		return (NULL);

	if (line[0] == '*')
	{
		files = files_array();
		for (ind = 0; files[ind]; ind++)
		{
			if (wildcmp(files[ind], line))
			{
				matched = str_to_arr(files[ind], matched);
			}
		}
		free_arr(files);
		match = str_join(matched, " ");
		free_arr(matched);
		if (match == NULL)
			return (line);

		free(line);
		return (match);
	}

	return (line);
}

/**
 * handle_variable - handles the "$" wildcard in input;
 * @line: CLI input;
 * Return: expanded string, the initial line or space;
 */

char *handle_variable(char *line)
{
	char *new = NULL, *kp_line = NULL;
	pid_t cur_pid = getpid();

	if (line == NULL)
		return (NULL);

	if (line[0] == '$')
	{
		if (line[1] == '\0')
			return (line);
		if (line[1] == '$')
		{
			new = num_to_str(cur_pid);
		}
		else if (line[1] == '?')
		{
			new = _getenv("xstat");
		}
		else if (line[1] == '.')
		{
			new = _strdup(".");
		}
		else
		{
			new = _str_slice(line, 1, _strlen(line));
			kp_line = _getenv(new);
			free(new);
			if (kp_line == NULL)
				new = _strdup(" ");
			else
			{
				new = _strdup(kp_line);
				free(kp_line);
			}
		}
		free(line);
		return (new);
	}

	return (line);
}

/**
 * files_array - computes an array of all files in the current directory;
 * Return: an array of filenames;
 */

char **files_array(void)
{
	unsigned int i;
	char **arr1 = NULL;
	struct dirent *dir_content = NULL;
	DIR *dir = NULL;

	for (i = 0; envpath[i] != NULL; i++)
	{
		arr1 = split_str(envpath[i], "=");
		if (match_command(arr1[0], "PWD"))
		{
			dir = opendir(arr1[1]);
			free_arr(arr1);
			break;
		}
		free_arr(arr1);
	}
	if (dir == NULL)
		return (NULL);

	arr1 = NULL;
	while (1)
	{
		dir_content = readdir(dir);
		if (dir_content == NULL)
			break;

		arr1 = str_to_arr(dir_content->d_name, arr1);
	}
	closedir(dir);

	return (arr1);
}
