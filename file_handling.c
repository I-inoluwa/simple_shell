#include "main.h"

/**
 * handle_file - handles file arguments in CLI;
 * @filename: file argument passed;
 * Return: returns xstat;
 */

int handle_file(char *filename)
{
	char c, *file_lines = NULL, *err_msg = NULL, *useless = NULL;
	int i = 0, fd = 0, xstat = -1, bytes = 0;

	if (filename == NULL)
		return (2);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		err_msg = join_strs("Can't open", filename, " ");
		useless = num_to_str(RC);
		error_out(FILENME, useless, err_msg, NULL);
		free(err_msg);
		free(useless);
		return (127);
	}
	while (1)
	{
		file_lines = malloc(sizeof(char) * 1024);
		if (file_lines == NULL)
			return (-1);

		for (i = 0; i < 1024; i++)
		{
			bytes = read(fd, &c, sizeof(char));
			if (bytes == -1 || bytes == 0 || c == '\n')
				break;
			file_lines[i] = c;
		}
		file_lines[i] = '\0';
		RC++;
		xstat = start_parse(file_lines);
		if (bytes == 0 || bytes == -1)
			break;
	}

	close(fd);
	return (xstat);
}
