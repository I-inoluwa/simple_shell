#include "main.h"

/**
 * snip_in_str - checks if a string (snip) can be found in another string;
 * @snip: the string to be searched for;
 * @str: the string being searched;
 * Return: returns the number of times snip is found in str.
 */

int snip_in_str(char *snip, char *str)
{
	size_t stlen = _strlen(str), snplen = _strlen(snip), ind = 0;
	size_t st = 0, end = snplen - 1;
	int count = 0;
	char *samp = NULL;

	if (snip == NULL || str == NULL)
		return (0);

	if (snplen > stlen)
		return (0);

	if (match_command(snip, str))
		return (1);

	for (ind = 0; ind <= stlen - snplen; ind++, st++, end++)
	{
		samp = _str_slice(str, st, end);
		if (match_command(samp, snip))
			count++;

		free(samp);
	}

	return (count);
}

/**
 * handle_OR - handles the presence of || in inputs;
 * @line: input line string;
 * Return: returns xstat;
 */

int handle_OR(char *line)
{
	size_t ind = 0, len = _strlen(line), fkeep = 0;
	int xstat = 0;
	char **args = NULL, *slice = NULL, *useless = 0;

	if (line == NULL)
		return (0);
	if (!(snip_in_str("||", line)))
		return (-1);

	while (line[ind])
	{
		if (ind > 0 && line[ind] == '|' && line[ind - 1] == '|')
		{
			if (!(is_in_quote(ind, line)))
			{
				slice = _str_slice(line, fkeep, ind - 2);
				if (slice == NULL)
				{
					useless = num_to_str(RC);
					error_out(FILENME, useless, "Syntax error", "\"||\" unexpected", NULL);
					free(useless);
					return (2);
				}
				xstat = start_parse(slice);
				if (xstat == 0)
					return (0);
				fkeep = ind + 1;
			}
		}
		if (ind == len - 1)
		{
			slice = _str_slice(line, fkeep, ind);
			args = handle_wild_cards(slice);
			xstat = (args == NULL) ? xstat : start_parse(_strdup(slice));
			free(slice), free_arr(args);
		}
		ind++;
	}
	return (xstat);
}


/**
 * handle_AND - handles the presence of && in inputs;
 * @line: input line string;
 * Return: returns xstat;
 */

int handle_AND(char *line)
{
	size_t ind = 0, len = _strlen(line), fkeep = 0;
	int xstat = 0;
	char **args = NULL, *slice = NULL, *useless = 0;

	if (line == NULL)
		return (0);
	if (!(snip_in_str("&&", line)))
		return (-1);

	while (line[ind])
	{
		if (ind > 0 && line[ind] == '&' && line[ind - 1] == '&')
		{
			if (!(is_in_quote(ind, line)))
			{
				slice = _str_slice(line, fkeep, ind - 2);
				if (slice == NULL)
				{
					useless = num_to_str(RC);
					error_out(FILENME, useless, "Syntax error", "\"&&\" unexpected", NULL);
					free(useless);
					return (2);
				}
				xstat = start_parse(slice);
				if (xstat != 0)
					return (xstat);
				fkeep = ind + 1;
			}
		}
		if (ind == len - 1)
		{
			slice = _str_slice(line, fkeep, ind);
			args = handle_wild_cards(slice);
			xstat = (args == NULL) ? xstat : start_parse(_strdup(slice));
			free(slice), free_arr(args);
		}
		ind++;
	}
	return (xstat);
}
