#include "main.h"

void str_slice(char *s1, int ind, int jnd, char *s2)
{
	int len = _strlen(s1);
	int i, j;

	if (s1 == NULL || s2 == NULL || jnd > len || ind > len || ind > jnd)
		return;

	if (ind < 0)
		ind = 0;

	for (i = ind, j = 0; (i <= jnd && s1[i]); i++, j++)
	{
		s2[j] = s1[i];
	}

	s2[j] = '\0';
}



/**
 * _str_slice - slices a string, and creates a buffer.
*/
char *_str_slice(char *str, int ind, int jnd)
{
	int len = abs(jnd - ind) + 2;
	char *buffer;

	/*will confirm conditions*/
	if (str == NULL || jnd < ind)
		return (NULL);

	buffer = malloc(sizeof(char) * len);
	if (buffer == NULL)
	{
		perror("Malloc failed");
		return (NULL);
	}
	buffer[0] = '\0';
	str_slice(str, ind, jnd, buffer);

	return (buffer);
}

char **str_to_arr(char *str, char **arr)
{
	char **new_array = NULL;
	size_t len = array_len(arr) + 2, i;

	if (arr == NULL)
	{
		arr = split_str(str, "");
		return (arr);
	}

	new_array = malloc(sizeof(char *) * len);
	if (new_array == NULL)
	{
		free_arr(new_array);
		perror("Malloc failed");
		return (arr);
	}
	new_array[0] = NULL;

	for (i = 0; arr[i] != NULL; i++)
	{
		new_array[i] = _strdup(arr[i]);
	}
	new_array[i] = _strdup(str);
	new_array[i + 1] = NULL;

	if (arr != NULL)
	{
		free_arr(arr);
	}
	
	return (new_array);
}
