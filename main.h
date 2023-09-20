#ifndef MAIN_H
#define MAIN_H

#include "structs.h"
#include "old.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

extern char **envpath;
extern char *FILENME;
extern unsigned int RC;

void define_global(char *arg);
void get_line(char *str);
char *ret_line();

int _putchar(char c);
void _print(char *str);
void error_out(char *filename, ...);

size_t _strlen(const char *s);
int check_space(char *str, char *delim);
int *get_str_len_alt(char *str, int ix, char *delim);
char **str_to_arr(char *str, char **arr);
char **split_str(char *str, char *delim);
int is_delim(char c, char *delim);
char *str_join(char **arr, char *delim);
int match_command(char *command, char *str);
char *join_strs(char *s1, char *s2, char *delim);
void str_slice(char *s1, int ind, int jnd, char *s2);
char *_str_slice(char *str, int ind, int jnd);
char **add_array(char **args, char **final);
char **array_slice(size_t ind, size_t jnd, char **array);

char *_realloc(char *line, ssize_t ad_len);

int get_cmd_per_line(void);
int get_extra(char **line);
int end_of_line(char *str);
int reget_line(char **line);

void handle_kill(int signal);
void handle_kill_extra(int signal);

wc_format *is_first(wc_format *c1, wc_format *c2, char *str);

int ignore_str(char *str, int ind, int jnd, char *ignstr);
int handle_semicolon(char *line);
int handle_comments(char *line);
int handle_space(char *line);
char **handle_wild_cards(char *line);
char *handle_asterisks(char *line);
char *handle_variable(char *line);
char **handle_no_quotes(char *line);
char **handle_quotes_rec(char *line);
char **handle_each_quote(char *line, wc_format q);
int handle_quotes(wc_format q1, wc_format q2, char *line);
int count_in_str(char c, char *str, char *ignore);
/*int snip_in_str(char *snip, char *str, int (*funct)());*/
int is_in_quote(size_t ind, char *line);
int check_num_quote(char *line);
int last_ind(char c, char *str, char *ignore);
int first_ix(char c, char *str, char *ignore);
char *add_quotes_to(char *line);

int start_parse(char *line);
int handle_exit(char **array, char *line);
int handle_builtins(char *args[]);
int handle_echo(char *args[]);
int handle_env(char *args[]);
int check_access(char *dir);
int change_dir(char *args[]);
int handle_setenv(char *args[]);
int handle_unsetenv(char *args[]);

int change_to_home(char *args[]);
int change_to_current(char *args[]);
int change_to_previous(char *args[]);
int change_to_old(char *args[]);
int change_to_dir(char *args[]);

int execute(char **args, char *linecpy);
char *get_path(char *command);
int start_execution(char *args[], char *path);

int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
char *_getenv(char *variable);
char **files_array(void);

int print_tab(char **array);
size_t array_len(char **array);
void free_arr(char **array);

int is_num(char *str);
int make_number(char *str);
char *num_to_str(unsigned int num);

#endif
