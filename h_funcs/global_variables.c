#include "main.h"

char **__environ;
char **envpath;
char *FILENME;
unsigned int RC;


void define_global(char *arg)
{
	size_t ind, len = array_len(__environ);

	envpath = malloc(sizeof(char *) * (len + 1));
	if (envpath == NULL)
		return;

	for (ind = 0; ind < len; ind++)
	{
		envpath[ind] = _strdup(__environ[ind]);
	}
	envpath[len] = NULL;

	FILENME = arg;
	RC = 0;
}

char *line;

void get_line(char *str)
{
	line = str;
}

char *ret_line()
{
	return (line);
}
