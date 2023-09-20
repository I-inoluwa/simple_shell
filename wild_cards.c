#include "main.h"

/**
 * is_first - function to check which quote comes first in a string;
 * @c1: first quote;
 * @c2: second quote;
 * @str: string to be checked;
 * Return: the quote that comes first, else NULL.
 */

wc_format *is_first(wc_format *c1, wc_format *c2, char *str)
{
	int ix1, ix2;

	if (str == NULL)
		return (0);

	ix1 = c1->first_ind, ix2 = c2->first_ind;
	if (ix1 < ix2)
		return (c1);
	else if (ix1 > ix2)
		return (c2);

	return (NULL);
}

/**
 * handle_wild_cards - handles wildcards in an input;
 * @line: line to be handled;
 * Return: returns an array of parsed strings;
 */

char **handle_wild_cards(char *line)
{
	/*if no wildcards, return as is*/
	/*else, for certain wildcards, handle them with functions*/
	/*first, do counting: ' and " take precedence"*/

	char **args;

	args = handle_quotes_rec(line);

	return (args);
}

/**
 * handle_quotes - checks if a line contains no, complete or incomplete quotes;
 * @q1: single quote;
 * @q2: double quote handling;
 * @line: input line;
 * Return: an integer based on what it is.
 */

int handle_quotes(wc_format q1, wc_format q2, char *line)
{
	wc_format *first, *second;
	int qflag = 0;

	first = is_first(&q1, &q2, line);
	if (first != NULL)
	{
		if (first == &q1)
		{
			second = &q2;
			qflag = 2;
		}
		else
		{
			second = &q1;
			qflag = 3;
		}

		if (first->count % 2 == 0)
		{
			if (first->last_ind < second->last_ind)
			{
				if (second->count % 2 == 0)
				{
					if (second->first_ind < first->last_ind)
						qflag = 1;
				}
				else
					qflag = 1;
			}
		}
		else
			qflag = 1;
	}

	return (qflag);
}
