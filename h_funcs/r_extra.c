#include "main.h"

int print_tab(char **array)
{
	int i;

	if (array == NULL)
		return (0);

	for (i = 0; array[i] != NULL; i++)
   	{
        	_print(array[i]);
    	}

	return (i);
}

size_t array_len(char **array)
{
	size_t i;

	if (array == NULL)
		return (0);

	for (i = 0; array[i] != NULL; i++)
   	;

	return (i);
}


void free_arr(char **array)
{
	int i;

	if (array == NULL)
	{
		return;
	}

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);
}


int match_command(char *command, char *str)
{
	int ind;

	if (command == NULL && str == NULL)
		return (1);
	if (command == NULL || str == NULL)
		return (0);
	
	for (ind = 0; str[ind]; ind++)
	{
		if (str[ind] != command[ind])
			break;
	}
	if (str[ind] == command[ind])
		return (1);

	return (0);
}
