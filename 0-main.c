#include "main.h"

/**
 * main - The main function of the shell;
 * @argc: count of number of inputs;
 * @argv: arguments passed to shell;
 * Return: Returns (0) on success;
 */

int main(int argc, char *argv[])
{
	int xstat = 0;

	(void)argc;

	define_global(argv[0]);

	if (array_len(argv) == 1)
	{
		xstat = get_cmd_per_line();
	}
	else
	{
		/*handle file arguments*/
	}

	free_arr(envpath);
	return (xstat);
}
