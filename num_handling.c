#include "main.h"

/**
 * num_to_str - converts a positive integer to a string of chars;
 * @num: number to be converted;
 * Return: mallocs a printable string, representing num.
 */

char *num_to_str(unsigned int num)
{
	char *str = NULL;
	unsigned int i = 1, keep_num = num;

	while (num / 10 > 0)
	{
		num = num / 10;
		i++;
	}

	str = malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	num = keep_num;
	while (i)
	{
		str[i - 1] = (num % 10) + '0';
		num /= 10;
		i--;
	}

	return (str);
}

/**
 * make_number - converts a printable num string to an integer;
 * @str: string to be converted;
 * Return: an integer;
 */

int make_number(char *str)
{
	int i, num = 0;
	char c;

	if (!(is_num(str)))
		return (-1);

	for (i = 0; (c = str[i]) != '\0'; i++)
	{
		if (i == 0 && c == '-')
		{
			num = -1;
			continue;
		}

		if ((c >= '0' && c <= '9'))
		{
			if (num == -1)
				num *= c - '0';
			else
				num = (num * 10) + (c - '0');
		}
	}

	return (num);
}

/**
 * is_num - checks if a string is a string of +ve num chars;
 * @str: string to be checked;
 * Return: returns (1) if true, (0) otherwise;
 */

int is_num(char *str)
{
	int i;
	char c;

	if (str == NULL)
		return (0);

	for (i = 0; (c = str[i]); i++)
	{
		if (!(c >= '0' && c <= '9'))
			return (0);
	}

	return (1);
}
