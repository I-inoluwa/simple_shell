#include "main.h"

/**
 * handle_kill - signal for handling (ctrl + c) exit;
 * @signal: ctrl signal to be handled;
 * Return: returns void;
 */

void handle_kill(int signal)
{
	char *line = NULL;

	_putchar('\n');
	line = ret_line();
	free(line);
	free_arr(envpath);
	exit(signal);
}

/**
 * handle_kill_extra - signal for handling (ctrl + c) exit;
 * @signal: signal to be handled;
 * Return: returns void;
 */

void handle_kill_extra(int signal)
{
	_putchar('\n');

	if (signal)
		return;
}

/**
 * get_cmd_per_line - gets command per line;
 * Return: returns an int to indicate success;
 */

int get_cmd_per_line(void)
{
	char *exit_stat = NULL, *line = NULL;
	long int xstat = 0, nbytes = 0;
	size_t len = 1024;

	while (1)
	{
		exit_stat = num_to_str(xstat);
		_setenv("xstat", exit_stat, 1);
		free(exit_stat);

		line = malloc(sizeof(char) * 1024);
		if (line == NULL)
		{
			free(line);
			return (127);
		}
		if (isatty(STDIN_FILENO))
			write(1, "# ", 2);

		get_line(line);
		signal(SIGINT, handle_kill);

		nbytes = getline(&line, &len, stdin);
		if (nbytes == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			return (xstat);
		}
		xstat = get_extra(&line);
		if (xstat)
			continue;

		RC++;

		xstat = start_parse(line);
	}
	return (xstat);
}

/**
 * end_of_line - checks if reading of line should continue;
 * @str: line being read;
 * Return: returns either 1 (TRUE) or 0 (FALSE);
 */
int end_of_line(char *str)
{
	size_t i = _strlen(str);

	if (check_num_quote(str) == 1)
		return (2);

	if (i > 1)
	{
		if (str[i - 2] == '\\')
		{
			if (i > 2)
			{
				if (str[i - 3] == '\\')
					return (0);
			}
			return (1);
		}
	}

	return (0);
}

/**
 * get_extra - assists in getting a new line;
 * @line: address of line to be read;
 * Return: returns xstat - success or failure;
 */
int get_extra(char **line)
{
	size_t i = 0;
	int xstat = 0, eol = 0;

	while (1)
	{
		eol = end_of_line(*line);
		if (!eol)
			break;

		i = _strlen(*line);
		(*line)[i - 1] = '\0';
		if (eol == 1)
			(*line)[i - 2] = '\0';

		xstat = reget_line(line);
		if (xstat)
			break;
	}

	return (xstat);
}
