#include "main.h"

/**
 * reget_line - function that gets an extra line to the existing line;
 * @line: address of the line to be added to;
 * Return: returns an integer to indicate success (0), or failure (1);
 */

int reget_line(char **line)
{
	char *new_line = NULL, *extra_line = NULL;
	ssize_t nbytes;
	size_t len = 256;

	write(1, "> ", 2);
	RC++;

	new_line = malloc(sizeof(char) * 256);
	if (new_line == NULL)
	{
		free(new_line);
		return (1);
	}

	/*new_line[0] = '\0';*/
	nbytes = getline(&new_line, &len, stdin);
	if (nbytes == -1)
	{
		free(*line);
		free(new_line);
		return (1);
	}
	extra_line = join_strs(*line, new_line, "");
	free(*line);
	*line = extra_line;

	free(new_line);

	return (0);
}

/**
 * _realloc - reallocates memory to an existing string;
 * @line: the existing string to be extended;
 * @ad_len: the size of the extra memory to be allocated;
 * Return: returns the newly allocated string.
 */

char *_realloc(char *line, ssize_t ad_len)
{
	ssize_t len = _strlen(line);
	char *new_line = NULL;

	if (line == NULL)
	{
		new_line = malloc(sizeof(char) * ad_len);
		new_line[0] = '\0';
		return (new_line);
	}

	new_line = malloc(sizeof(char) * (len + ad_len - 1));
	if (new_line == NULL)
	{
		free(new_line);
		return (line);
	}
	new_line[0] = '\0';

	new_line = _strncpy(new_line, line, len + 1);

	return (new_line);
}
