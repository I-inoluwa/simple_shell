#include "main.h"

/**
 * array_slice - returns a copy of a slice of an array;
 * @ind: start index to be sliced;
 * @jnd: end index of slicing (including end index);
 * @array: array to be sliced from;
 * Return: returns a new array;
 */

char **array_slice(size_t ind, size_t jnd, char **array)
{
	size_t i, len = array_len(array);
	char **new_array = NULL;

	if (array == NULL || ind > len || jnd > len || ind > jnd)
		return (array);

	new_array = malloc(sizeof(char *) * (jnd - ind + 2));
	if (new_array == NULL)
	{
		free(new_array);
		return (NULL);
	}

	for (i = 0; i <= (jnd - ind); i++)
	{
		new_array[i] = _strdup(array[ind + i]);
	}
	new_array[i] = NULL;

	return (new_array);
}

/**
 * add_quotes_to - adds quotes to a string;
 * @line: string to be manipulated;
 * Return: a quoted string;
 */

char *add_quotes_to(char *line)
{
	size_t ind, len = _strlen(line);
	char *new_line;

	if (line == NULL)
		return (NULL);

	new_line = malloc(sizeof(char) * len + 3);
	if (new_line == NULL)
	{
		free(new_line);
		return (line);
	}
	new_line[0] = '\'';

	for (ind = 1; line[ind - 1]; ind++)
	{
		new_line[ind] = line[ind - 1];
	}
	new_line[ind] = '\'';
	new_line[ind + 1] = '\0';

	free(line);

	return (new_line);
}

/**
 * check_access - checks if a directory is valid or has access permissions;
 * @dir: name of directory to be checked;
 * Return: (0) success, or (-1) fail;
 */

int check_access(char *dir)
{
	char *rc = NULL, *err = NULL;

	if (access(dir, X_OK | F_OK) != 0)
	{
		rc = num_to_str(RC);
		if (errno == ENOENT)
		{
			err = join_strs("can't cd to", dir, " ");
			error_out(FILENME, rc, "cd", err, NULL);
		}
		else
		{
			err = join_strs("can't cd to", dir, " ");
			error_out(FILENME, rc, "cd", err, NULL);
		}
		free(rc);
		free(err);
		return (1);
	}

	return (0);
}

/**
 * check_num_quote - checks the balance of quotes in the input line;
 * @line: CLI input;
 * Return: (1) if unbalanced, (0) if no quote, (2) or (3) if balanced;
 */

int check_num_quote(char *line)
{
	int qflag = 0;
	char *buf1 = "\\\'", *buf2 = "\\\"";
	wc_format q1 = {0, 0, 0, NULL, '\''}, q2 = {0, 0, 0, NULL, '\"'};

	if (line == NULL)
		return (0);

	q1.ignore = buf1, q2.ignore = buf2;
	q1.count = count_in_str(q1.c, line, buf1);
	q2.count = count_in_str(q2.c, line, buf2);
	q1.last_ind = last_ind(q1.c, line, buf1);
	q2.last_ind = last_ind(q2.c, line, buf2);
	q1.first_ind = first_ix(q1.c, line, buf1);
	q2.first_ind = first_ix(q2.c, line, buf2);

	qflag = handle_quotes(q1, q2, line);

	return (qflag);
}

/**
 * is_in_quote - tells if a character of a line is in quotes;
 * @ind: index of character;
 * @line: string input;
 * Return: returns (0) if not in quote, and (1) if in quote;
 */

int is_in_quote(size_t ind, char *line)
{
	int in_quote1 = 0, in_quote2 = 0;
	size_t i = 0;

	if (line == NULL)
		return (0);

	if (ind > _strlen(line))
		return (0);

	for (i = 0; i < ind; i++)
	{
		if (line[i] == '\"')
			in_quote1 = !in_quote1;
		if (line[i] == '\'')
			in_quote2 = !in_quote2;
	}

	return (in_quote1 || in_quote2);
}
