#ifndef OLD_H
#define OLD_H

char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
int wildcmp(char *s1, char *s2);
int is_asterisk(char *str, const int i, int count);
int check_char(char *str1, char *str2, int i, int j, int t);

#endif
