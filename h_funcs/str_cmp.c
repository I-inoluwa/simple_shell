#include "main.h"

/**
 * wildcmp - compares two strings.
 * @s1: string to be compared with;
 * @s2: string 2. Contains a asterisk, *.
 * Return: returns (1) if strings are identical, else (0);
*/

int wildcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);

	if (s1 == NULL && s2 == NULL)
		return (1);

	return (check_char(s1, s2, 0, 0, 0));
}


/**
 * is_asterisk - checks if a character in a string is '*';
 * @str: string to be checked;
 * @i: start index of the check;
 * @count: number of '*' characters present;
 * Return: returns the number of '*' characters matched;
*/

int is_asterisk(char *str, const int i, int count)
{
	if (str[i + count] == '*')
		return (is_asterisk(str, i, ++count));

	return (count);
}


/**
 * check_char - checks if two strings match;
 * takes the asterisk into consideration;
 * @str1: first string to be compared against;
 * @str2: second string, may contain a asterisk;
 * @i: index of first string;
 * @j: index of second string;
 * @t: keeps the index of the char after the last '*' matched;
 * Return: returns (1) if strings match, else (0);
*/

int check_char(char *str1, char *str2, int i, int j, int t)
	{
		if ((str1[i] == '\0') && (str2[j] == '\0'))
			return (1);

		if (str2[j] == '*')
		{
			j += is_asterisk(str2, j, 0);
			t = j;
			return (check_char(str1, str2, i, j, t));
		}

		if (str1[i] == str2[j])
			return (check_char(str1, str2, ++i, ++j, t));

		if (str1[i] == '\0')
			return (0);

		if (j > 0 && str2[j - 1] == '*')
			return (check_char(str1, str2, ++i, j, t));

		if (str1[i] != str2[j])
		{
			j = t;
			return (check_char(str1, str2, ++i, j, t));
		}

		return (0);
	}
