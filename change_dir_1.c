#include "main.h"

/**
 * change_to_home - function to handle cd to HOME directory;
 * @args: array of command-line arguments;
 * Return: (0) on success, (2) on failure;
 */

int change_to_home(char *args[])
{
	/*To get the HOME dir and cd there.*/
	char *home_dir = _getenv("HOME"), *old_dir = NULL;

	if (home_dir == NULL)
		return (0);

	(void)args;

	if (check_access(home_dir))
	{
		free(home_dir);
		return (2); /*or (0)*/
	}

	old_dir = _getenv("PWD");
	if (old_dir == NULL)
		old_dir = getcwd(old_dir, 1024);

	if (chdir(home_dir) == -1)
	{
		free(old_dir);
		return (0);
	}
	_setenv("OLDPWD", old_dir, 1);
	_setenv("PWD", home_dir, 1);

	free(home_dir);
	free(old_dir);

	return (0);
}

/**
 * change_to_current - cd to the current directory;
 * @args: array of command-line arguments;
 * Return: returns (0) on success, (2) otherwise;
 */

int change_to_current(char *args[])
{
	char *wd = _getenv("PWD");

	if (wd == NULL)
		wd = getcwd(wd, 1024);

	(void)args;
	if (chdir(wd) == -1)
		return (2);

	_setenv("OLDPWD", wd, 1);
	_setenv("PWD", wd, 1);

	free(wd);

	return (0);
}

/**
 * change_to_previous - handles cd to the parent directory;
 * @args: array of command-line arguments;
 * Return: returns (0) on success, (2) otherwise;
 */

int change_to_previous(char *args[])
{
	char *wd = NULL, *nwd = NULL, *home = NULL;
	char **path_arr = NULL, **new_arr = NULL;

	if (wd == NULL)
		wd = getcwd(wd, 1024);

	(void)args;

	home = _getenv("HOME");
	if (match_command(home, wd) || match_command("/", wd))
		nwd = _strdup("/");
	else
	{
		path_arr = split_str(wd, "/\n");
		/*free the last item first;*/
		new_arr = array_slice(0, array_len(path_arr) - 2, path_arr);
		nwd = str_join(new_arr, "/");
		free_arr(path_arr);
		free_arr(new_arr);
	}
	free(home);

	if (check_access(nwd))
	{
		free(wd);
		free(nwd);
		return (2);
	}
	chdir(nwd);

	_setenv("OLDPWD", wd, 1);
	_setenv("PWD", nwd, 1);

	free(wd);
	free(nwd);
	return (0);
}

/**
 * change_to_old - handles cd to previously accessed directory;
 * @args: array of command-line arguments;
 * Return: returns (0) on success, (2) otherwise;
 */

int change_to_old(char *args[])
{
	char *old_dir = _getenv("OLDPWD");
	char *cur_dir = NULL;

	cur_dir = getcwd(cur_dir, 1024);
	if (old_dir == NULL)
	{
		_print(cur_dir);
		free(old_dir);
		free(cur_dir);
		return (0);
	}
	(void)args;

	if (check_access(old_dir))
	{
		free(cur_dir);
		free(old_dir);
		return (2);
	}
	chdir(old_dir);

	_setenv("PWD", old_dir, 1);
	_setenv("OLDPWD", cur_dir, 1);

	free(cur_dir);

	_print(old_dir);

	free(old_dir);

	return (0);
}

/**
 * change_to_dir - handles cd to directory specified as argument;
 * @args: array of command-line arguments;
 * Return: returns (0) on success, (2) otherwise;
 * outputs an error statement to STDERR on error;
 */

int change_to_dir(char *args[])
{
	char *old_dir = NULL, *new_dir = NULL;
	char **arr = NULL;

	old_dir = getcwd(old_dir, 1024);

	if (check_access(args[1]))
	{
		free(old_dir);
		return (2);
	}
	chdir(args[1]);

	if (args[1][0] != '/')
	{
		arr = split_str(old_dir, "/");
		arr = str_to_arr(args[1], arr);
		new_dir = str_join(arr, "/");
		free_arr(arr);
	}
	else
		new_dir = _strdup(args[1]);

	_setenv("PWD", new_dir, 1);
	_setenv("OLDPWD", old_dir, 1);

	free(old_dir);
	free(new_dir);

	return (0);
}
