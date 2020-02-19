#ifndef SMARTINPUT_H
#define SMARTINPUT_H

#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

int get_short(short *value);

int get_ushort(unsigned short *value);

int get_int(int *value);

int get_uint(unsigned int *value);

int get_long(long *value);

int get_ulong(unsigned long *value);

int get_llong(long long *value);

int get_ullong(unsigned long long *value);

int get_float(float *value);

int get_double(double *value);

int get_ldouble(long double *value);

int get_line(char *s, int len);


int fget_short(short *value, FILE *stream);

int fget_ushort(unsigned short *value, FILE *stream);

int fget_int(int *value, FILE *stream);

int fget_uint(unsigned int *value, FILE *stream);

int fget_long(long *value, FILE *stream);

int fget_ulong(unsigned long *value, FILE *Istream);

int fget_llong(long long *value, FILE *stream);

int fget_ullong(unsigned long long *value, FILE *stream);

int fget_float(float *value, FILE *stream);

int fget_double(double *value, FILE *stream);

int fget_ldouble(long double *value, FILE *stream);

int fget_line(char *s, int len, FILE *stream);




#endif

