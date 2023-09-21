#include "main.h"

/**
 * start_parse - takes the input line, and starts the parsing;
 * @line: line argument that is a string;
 * Return: returns exit status (xstat);
 */

int start_parse(char *line)
{
	char **args = NULL;
	int xstat = 0, ind = 0;

	int (*funct_ptr[4])(char *line) = {
	    handle_comments,
	    handle_OR,
	    handle_AND,
	    handle_semicolon};

	if (handle_space(line))
	{
		free(line);
		return (0);
	}

	for (ind = 0; ind < 4; ind++)
	{
		xstat = funct_ptr[ind](line);
		if (xstat > -1)
		{
			free(line);
			return (xstat);
		}
	}

	args = handle_wild_cards(line);

	xstat = execute(args, line);
	free(line);

	return (xstat);
}

/**
 * handle_semicolon - function to handle semicolons in input command;
 * @line: non-parsed input string;
 * Return: returns the last exit status, or (-1) on failure;
 */

int handle_semicolon(char *line)
{
	char *new_args = NULL, *useless = NULL, **args = NULL;
	size_t ind = 0, len = _strlen(line), fkeep = 0;
	int xstat = -1;

	if (line == NULL)
		return (0);
	if (count_in_str(';', line, "") == 0)
		return (xstat);

	while (line[ind])
	{
		if (line[ind] == ';')
		{
			if (!(is_in_quote(ind, line)))
			{
				new_args = _str_slice(line, fkeep, ind - 1);
				if (new_args == NULL)
				{
					useless = num_to_str(RC);
					/*error_out(FILENME, useless, "Syntax error", "\";\" unexpected", NULL);*/
					free(useless);
					return (2);
				}
				args = handle_wild_cards(new_args);
				xstat = execute(args, new_args);
				free(new_args);
				fkeep = ind + 1;
			}
		}
		if (ind == len - 1)
		{
			new_args = _str_slice(line, fkeep, ind);
			args = handle_wild_cards(new_args);
			xstat = (args == NULL) ? xstat : execute(args, new_args);
			free(new_args);
			fkeep = ind + 1;
		}
		ind++;
	}
	return (xstat);
}

/**
 * handle_comments - function to handle comments in input command;
 * @line: non-parsed input string;
 * Return: returns the exit status, or (-1) on failure;
 */

int handle_comments(char *line)
{
	char *new_args = NULL;
	size_t ind = 0;
	int xstat = -1;

	if (line == NULL)
		return (0);

	if (count_in_str('#', line, "") == 0)
		return (xstat);

	while (line[ind])
	{
		if (line[ind] == '#')
		{
			if (ind == 0)
				return (0);
			if (ind > 0 && line[ind - 1] == ' ')
				if (!(is_in_quote(ind, line)))
				{
					new_args = _str_slice(line, 0, ind - 1);
					xstat = start_parse(new_args);

					return (xstat);
				}
		}

		ind++;
	}

	return (xstat);
}

/**
 * handle_space - function to handle when the input is only spaces;
 * @line: non-parsed input string;
 * Return: returns (1) on success, (0) on failure;
 */

int handle_space(char *line)
{
	size_t ind = 0;

	if (line == NULL)
		return (1);

	for (ind = 0; line[ind] == ' '; ind++)
		;

	if (line[ind] == '\0')
		return (1);

	return (0);
}
