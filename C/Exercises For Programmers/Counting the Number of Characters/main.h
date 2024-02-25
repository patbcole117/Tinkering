#include <stdlib.h>

int get_length(char *buf);
int get_length_recursive(char *buf, int len);
int get_length_recursive_ternary(char *buf, int len);
char *safe_gets(char *buf, int size, FILE *stream);