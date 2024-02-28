#ifndef RSTDIN_H_
#define RSTDIN_H_

double read_double_from_stdin_and_flush(int *idx, int *err);
int read_string_from_stdin_and_flush(int size, char *str_buf);
long read_long_from_stdin_and_flush(int *idx, int *err);

#endif
