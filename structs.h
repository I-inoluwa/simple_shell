#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * struct inp - input_str format;
 * @err: error value;
 * @line: string input.
 *
 * Description: an input_str format.
 */

typedef struct inp
{
	int err;
	char *line;
} input_str;

/**
 * struct wc- wc_format
 * @count: count of char
 * @first_ind: first index of char;
 * @last_ind: last index of char;
 * @ignore: ignore string;
 * @c: wildcard;
 *
 * Description: a wildcard format
 */

typedef struct wc
{
	int count;
	int first_ind;
	int last_ind;
	char *ignore;
	char c;
} wc_format;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 * struct fmt - a format for handling builtin functions;
 * @command: builtin command to be handled;
 * @funct: function to act on the command;
 *
 * Description: a format to help simplify processes
 */

typedef struct fmt
{
	char *command;
	int (*funct)();
} built_in_format;

#endif
