#include "main.h"

/**
 * _strdup - returns a pointer to a memory space, containing a str;
 * @str: a string to be copied.
 * Return: returns a pointer to a memory space;
 */

char *_strdup(char *str)
{
	char *s;
	int i, strrlen;

	if (str == NULL)
		return (NULL);
	strrlen = 0;
	for (i = 0; str[i]; i++)
	{
		strrlen++;
	}
	s = malloc((strrlen + 1) * sizeof(char));
	if (s == NULL)
	{
		free(s);
		return (NULL);
	}

	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';

	return (s);
}


/**
 * str_concat - concatenates two strings.
 * @s1: first part of the strings to be concatenated
 * @s2: Second string to be concatenated.
 * Return: returns a pointer to a memory space;
 */

char *str_concat(char *s1, char *s2)
{
	char *str;
	int i, j, strrlen;

	if (s1 == NULL)
	{
		s1 = "";
	}
	if (s2 == NULL)
	{
		s2 = "";
	}

	strrlen = 0;
	for (i = 0; s1[i] || s2[i]; i++)
		strrlen++;

	str = malloc(sizeof(char) * strrlen);

	if (str == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (*(s1 + i))
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		*(str + i) = *(s2 + j);
		j++;
		i++;
	}

	*(str + i) = '\0';
	return (str);
}

/**
  * _strncpy - copies a string.
  * @dest: output string.
  * @src: string to be copied.
  * @n: byte of src to be copied.
  * Return: returns dest.
  */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; (i < n) && src[i] != '\0'; i++)
		dest[i] = src[i];

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
