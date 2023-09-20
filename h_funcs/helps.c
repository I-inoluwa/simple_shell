#include "main.h"

void _print(char *str)
{
	if (str == NULL)
		return;

	write(STDOUT_FILENO, str, _strlen(str));
	_putchar('\n');
}


size_t _strlen(const char *s)
{
	size_t length = 0;

	if (s == NULL)
		return (0);

	if (s[0] == '\0')
		return (0);

	while (s[length])
	{
		length++;
	}

	return (length);
}

char *join_strs(char *s1, char *s2, char *delim)
{
	int i, j, k;
	size_t len;
	char *str;

	if (s1 == NULL || s2 == NULL || delim == NULL)
		return (NULL);

	len = _strlen(s1) + _strlen(s2) + _strlen(delim) + 1;
	str = malloc(sizeof(char) * len);
	if (str == NULL)
	{
		perror("Malloc fail");
		free(str);
		return (NULL);
	}

	for (i = 0; s1[i]; i++)
		str[i] = s1[i];
	for (j = 0; delim[j]; j++, i++)
		str[i] = delim[j];
	for (k = 0; s2[k]; k++, i++)
		str[i] = s2[k];
	str[i] = '\0';

	return (str);
}
