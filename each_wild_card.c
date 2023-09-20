#include "main.h"

/**
 * add_array - extends a string array by items of another.
 * @args: array containing strings to be added;
 * @final: array to be added to;
 * Return: returns the updated array.
 */

char **add_array(char **args, char **final)
{
	size_t ind = 0, i = 0, len = array_len(final);
	size_t arglen = array_len(args);
	char **main_args;

	if (args == NULL)
		return (final);

	main_args = malloc(sizeof(char *) * (len + arglen + 1));
	main_args[0] = NULL;

	/*copy and append final elements to main_arg*/
	for (ind = 0; ind < len; ind++)
		main_args[ind] = _strdup(final[ind]);

	free_arr(final);

	/*copy and append args element to main_arg*/
	for (i = 0; ind < len + arglen; ind++, i++)
	{
		main_args[ind] = _strdup(args[i]);
	}
	free_arr(args);
	main_args[ind] = NULL;

	return (main_args);
}

/**
 * handle_each_quote - handles quotations in input lines;
 * @line: Input string of commands;
 * @q: a struct type to define a wildcard.
 * Return: returns an array of parsed CLI arguments;
 */

char **handle_each_quote(char *line, wc_format q)
{
	size_t len = _strlen(line);
	char **fin = NULL, *keep = NULL;
	/*char *initial_arr[] = {"before", "during", "after", NULL};*/
	char *initial_arr[] = {NULL, NULL, NULL, NULL};
	int f_ind = 0;

	initial_arr[0] = _str_slice(line, 0, q.first_ind - 1);
	keep = _str_slice(line, q.first_ind + 1, len - 1);
	f_ind = first_ix(q.c, keep, q.ignore) + q.first_ind + 1;
	initial_arr[1] = _str_slice(line, q.first_ind + 1, f_ind - 1);
	free(keep);
	keep = _str_slice(line, f_ind + 1, len - 1);
	if (keep == NULL)
		free(keep);
	else
	{
		initial_arr[2] = keep;
	}

	fin = add_array(handle_no_quotes(initial_arr[0]), fin);
	fin = str_to_arr(initial_arr[1], fin);
	free(initial_arr[0]);
	free(initial_arr[1]);
	if (initial_arr[2] != NULL)
	{
		fin = add_array(handle_quotes_rec(initial_arr[2]), fin);
		free(initial_arr[2]);
	}

	return (fin);
}

/**
 * handle_quotes_rec - recursively parses a string, considering quotes.
 * @line: Input string of commands;
 * Return: returns an array of parsed CLI arguments;
 */

char **handle_quotes_rec(char *line)
{
	int qflag = 0;
	char **args = NULL;
	char *buf1 = "\\\'", *buf2 = "\\\"";
	wc_format q1 = {0, 0, 0, NULL, '\''}, q2 = {0, 0, 0, NULL, '\"'};

	if (line == NULL)
		return (NULL);

	q1.ignore = buf1, q2.ignore = buf2;
	q1.count = count_in_str(q1.c, line, buf1);
	q2.count = count_in_str(q2.c, line, buf2);
	q1.last_ind = last_ind(q1.c, line, buf1);
	q2.last_ind = last_ind(q2.c, line, buf2);
	q1.first_ind = first_ix(q1.c, line, buf1);
	q2.first_ind = first_ix(q2.c, line, buf2);

	qflag = handle_quotes(q1, q2, line);

	switch (qflag)
	{
	case (0):
		/*no quote in string*/
		args = handle_no_quotes(line);
		return (args);
	case (2):
		/*/' comes first*/
		args = handle_each_quote(line, q1);
		return (args);
	case (3):
		args = handle_each_quote(line, q2);
		return (args);
	}

	return (args);
}

/**
 * handle_no_quotes - parses the section of input line with no quotes;
 * @line: Input string of commands;
 * Return: returns an array of parsed CLI arguments;
 */

char **handle_no_quotes(char *line)
{
	char **args = NULL, **new_args = NULL, *delim = " \t\n";
	size_t ind;

	if (line == NULL)
		return (NULL);

	args = split_str(line, delim);
	for (ind = 0; ind < array_len(args); ind++)
	{
		args[ind] = handle_asterisks(args[ind]);
		new_args = str_to_arr(args[ind], new_args);
		if (args[ind][0] == ' ')
		{
			free(new_args[ind]);
			new_args[ind] = _str_slice(args[ind], 1, _strlen(args[ind]) - 1);
			free(args[ind]);
			args[ind] = _strdup(new_args[ind]);
			continue;
		}
		args[ind] = handle_variable(args[ind]);
		free(new_args[ind]);
		new_args[ind] = _strdup(args[ind]);
	}
	free_arr(new_args);

	return (args);
}
