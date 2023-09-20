#include "main.h"

/**
 * ignore_str - confirms i a slice of a string is to be ignored;
 * @str: string to be sliced;
 * @ind: first index;
 * @jnd: last index;
 * @ignstr: string to be ignored;
 * Return: integers true or false.
 */

int ignore_str(char *str, int ind, int jnd, char *ignstr)
{
	char buffer[3];

	if (str == NULL || ignstr == NULL)
		return (0);

	buffer[0] = '\0';
	str_slice(str, ind, jnd, buffer);
	if (match_command(buffer, ignstr))
		return (1);

	return (0);
}

/**
 * last_ind - checks the last index of a character in a string;
 * @c: character to be checked;
 * @str: input string
 * @ignore: strings to be ignored;
 * Return: the last index;
 */

int last_ind(char c, char *str, char *ignore)
{
	int t = 0, last_i = -1;

	if (str == NULL)
		return (last_i);

	for (t = 0; str[t]; t++)
	{
		if (t > 1)
		{
			if (ignore_str(str, t - 1, t, ignore))
				continue;
		}
		if (str[t] == c)
		{
			last_i = t;
		}
	}

	return (last_i);
}

/**
 * count_in_str - counts the number of char in a string;
 * @c: char to be counted;
 * @str: string input;
 * @ignore: ignore string;
 * Return: count of char in string.
 */

int count_in_str(char c, char *str, char *ignore)
{
	int t = 0, count = 0;

	if (str == NULL)
		return (count);

	for (t = 0; str[t]; t++)
	{
		if (t > 1)
		{
			if (ignore_str(str, t - 1, t, ignore))
				continue;
		}
		if (str[t] == c)
		{
			count++;
		}
	}

	return (count);
}

/**
 * first_ix - checks the first index of a character in a string;
 * @c: character to be checked;
 * @str: input string
 * @ignore: strings to be ignored;
 * Return: the first index;
 */

int first_ix(char c, char *str, char *ignore)
{
	int t;

	if (str == NULL)
		return (-1);

	for (t = 0; str[t]; t++)
	{
		if (t > 1)
		{
			if (ignore_str(str, t - 1, t, ignore))
				continue;
		}
		if (str[t] == c)
			return (t);
	}

	return (_strlen(str));
}
