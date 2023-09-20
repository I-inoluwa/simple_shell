#include "main.h"

char *str_join(char **arr, char *delim)
{
	int i, arr_len = array_len(arr);
	char *new_str = NULL, *keep_str = NULL;

	if (arr == NULL || delim == NULL)
		return (NULL);

	keep_str = join_strs(delim, arr[0], "");
	for (i = 1; i < arr_len; i++)
	{
		new_str = join_strs(keep_str, arr[i], delim);
		free(keep_str);
		keep_str = _strdup(new_str);
		free(new_str);
	}

	if (keep_str == NULL)
	{
		free(keep_str);
		return (NULL);
	}

	return (keep_str);
}
