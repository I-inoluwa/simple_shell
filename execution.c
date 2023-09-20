#include "main.h"

/**
 * start_execution - handles the execve section of the shell;
 * @args: the array of commands (command + args) to the executed;
 * @path: the path to the command to be executed;
 * Return: returns the exit status;
 */

int start_execution(char *args[], char *path)
{
	pid_t cpid;
	int wstatus, xstat;
	/*__sighandler_t sigval = 0;*/

	cpid = fork();
	if (cpid == -1)
	{
		perror("Fork failed");
		return (127);
	}
	if (cpid == 0)
	{
		if (execve(path, args, envpath) == -1)
		{
			exit(0);
		}
		return (2);
	}
	else
	{
		signal(SIGINT, handle_kill_extra);
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			xstat = WEXITSTATUS(wstatus);
			return (xstat);
		}
		else
			return (0);
	}
}

/**
 * execute - main execution function of the shell;
 * @args: an array of strings to be executed;
 * @linecpy: the initial line input, before parsing;
 * Return: returns exit status;
 */

int execute(char **args, char *linecpy)
{
	char *path = NULL, *alx = NULL, *useless = NULL;
	int xstat = 0;

	if (args == NULL)
		return (0);

	if (handle_exit(args, linecpy) != -1)
	{
		free_arr(args);
		return (2);
	}

	xstat = handle_builtins(args);
	if (xstat >= 0)
	{
		free_arr(args);
		return (xstat);
	}

	path = get_path(args[0]);
	if (path != NULL)
	{
		xstat = start_execution(args, path);
		free(path);
		free_arr(args);
		return (xstat);
	}
	alx = _strdup(args[0]);
	free_arr(args);

	useless = num_to_str(RC);
	error_out(FILENME, useless, alx, "not found", NULL);
	free(alx);
	free(useless);

	return (127);
}

/**
 * handle_builtins - function to handle built-in commands;
 * @args: array of strings, with string[0] being the builtin command;
 * Return: returns the exit status after execution;
 */

int handle_builtins(char *args[])
{
	int ind, xstat;
	built_in_format builtins[] = {
	    {"cd", change_dir},
	    /*{"echo", handle_echo},*/
	    {"env", handle_env},
	    {"setenv", handle_setenv},
	    {"unsetenv", handle_unsetenv},
	    {NULL, NULL}
	    };

	/*I thought echo was a builtin.. smh*/
	for (ind = 0; builtins[ind].command != NULL; ind++)
	{
		if (match_command(builtins[ind].command, args[0]))
		{
			xstat = builtins[ind].funct(args);
			return (xstat);
		}
	}

	return (-1);
}

/**
 * error_out - prints the error message to STDERR;
 * @filename: name of the executable;
 * Return: returns void;
 */

void error_out(char *filename, ...)
{
	va_list args;
	char *str;

	write(STDERR_FILENO, filename, _strlen(filename));

	va_start(args, filename);
	while (1)
	{
		str = va_arg(args, char *);
		if (str == NULL)
			break;
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, str, _strlen(str));
	}
	va_end(args);

	write(STDERR_FILENO, "\n", 1);
}
