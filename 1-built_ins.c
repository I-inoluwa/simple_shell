#include "main.h"

/**
 * handle_exit - function to handle exit command;
 * @array: array of command line arguments;
 * @line: input command;
 * Return: (2) or (-1) on failure;
 */

int handle_exit(char **array, char *line)
{
	int status = 0;
	char *useless = NULL, *new = NULL;

	if (match_command("exit", array[0]))
	{
		if (array[1] == NULL)
		{
			free_arr(array);
			free(line);
			new = _getenv("xstat");
			if (new == NULL)
				exit(0);
			status = make_number(new);
			free(new);
			free_arr(envpath);
			exit(status);
		}

		if (!(is_num(array[1])))
		{
			useless = num_to_str(RC);
			error_out(FILENME, useless, array[0], "Illegal number", array[1], NULL);
			free(useless);
			return (2);
		}
		status = make_number(array[1]);
		free_arr(array);
		free_arr(envpath);
		free(line);
		exit(status);
	}

	return (-1);
}

/**
 * change_dir - handles the cd builtin;
 * @args: arguments passed to the command line;
 * Return: The exit status of the command;
 */

int change_dir(char *args[])
{
	int ind, xstat;
	built_in_format funcs[] = {
	    {NULL, change_to_home},
	    {".", change_to_current},
	    {"..", change_to_previous},
	    {"-", change_to_old},
	    {NULL, change_to_dir}
	    };

	if (args == NULL || array_len(args) > 2)
		return (0);

	if (match_command("cd", args[0]))
	{
		for (ind = 0; ind < 4; ind++)
		{
			if (match_command(funcs[ind].command, args[1]))
			{
				xstat = (funcs[ind].funct(args));

				return (xstat);
			}
		}
		xstat = funcs[ind].funct(args);

		return (xstat);
	}

	return (-1);
}

/**
 * handle_echo - handles the echo command (or was supposed to);
 * @args: array of command-line arguments;
 * Return: (0) on success, (-1) on failure;
 */

int handle_echo(char *args[])
{
	int ind = 0;

	if (match_command("echo", args[0]))
	{
		for (ind = 1; args[ind] != NULL; ind++)
		{
			write(STDOUT_FILENO, args[ind], _strlen(args[ind]));
			if (args[ind + 1] != NULL)
				_putchar(' ');
		}
		_putchar('\n');
		return (0);
	}

	return (-1);
}


/**
 * handle_env - handles the env builtin command;
 * @args: array of command-line arguments;
 * Return: (0) on success, (2) or (-1) on failures;
 */

int handle_env(char *args[])
{
	size_t i;
	size_t arrlen = array_len(envpath);
	char **check_arr = NULL;

	if (match_command(args[0], "env"))
	{
		if (array_len(args) == 1)
		{
			for (i = 0; i < arrlen; i++)
			{
				check_arr = split_str(envpath[i], "=");
				if (!(match_command(check_arr[0], "xstat")))
					_print(envpath[i]);

				free_arr(check_arr);
			}

			return (0);
		}
		else
		{
			args[1] = add_quotes_to(args[1]);
			error_out("env", args[1], "No such file or directory", NULL);

			return (2);
		}
	}

	return (-1);
}

/**
 * handle_setenv - handles the setenv builtin;
 * @args: array of CLI arguments;
 * Return: exit status (i.e., 0, 2 or -1);
 */

int handle_setenv(char *args[])
{
	int xstat = 0;

	if (array_len(args) != 3)
	{
		/*_print("syntax: setenv VARIABLE VALUE");*/
		return (2);
	}

	xstat = _setenv(args[1], args[2], 1);
	/*if (xstat == 2)*/
	/*	_print("Setenv CALL failure");*/

	return (xstat);
}
