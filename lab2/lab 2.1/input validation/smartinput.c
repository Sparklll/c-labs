#include "smartinput.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BUF_SIZE 256


static int fget_input(char *s, size_t len, FILE *stream) {
    size_t i = 0;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n')
        if (!isspace(ch))
            break;

    while (ch != EOF && ch != '\n') {
        if (i < len - 1)
            s[i++] = ch;

        ch = fgetc(stream);
    }
    s[i] = '\0';

    if ((i == 0 && ch == EOF) || ferror(stream))
        return EOF;

    return SUCCESS;
}


int fget_short(short *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtol(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0'
        || v > SHRT_MAX || v < SHRT_MIN)
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_ushort(unsigned short *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    unsigned long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    size_t i = 0;
    while (isspace(buffer[i]))
        ++i;
    if (buffer[i] == '-')
        return FAILURE;

    errno = 0;
    v = strtoul(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0'
        || v > USHRT_MAX)
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_int(int *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtol(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0'
        || v > INT_MAX || v < INT_MIN)
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_uint(unsigned int *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    unsigned long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    size_t i = 0;
    while (isspace(buffer[i]))
        ++i;
    if (buffer[i] == '-')
        return FAILURE;

    errno = 0;
    v = strtoul(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0'
        || v > UINT_MAX)
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_long(long *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtol(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_ulong(unsigned long *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    unsigned long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    size_t i = 0;
    while (isspace(buffer[i]))
        ++i;
    if (buffer[i] == '-')
        return FAILURE;

    errno = 0;
    v = strtoul(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_llong(long long *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    long long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtoll(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_ullong(unsigned long long *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    unsigned long long v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    size_t i = 0;
    while (isspace(buffer[i]))
        ++i;
    if (buffer[i] == '-')
        return FAILURE;

    errno = 0;
    v = strtoull(buffer, &temp, 10);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}

int fget_float(float *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    float v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtof(buffer, &temp);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_double(double *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    double v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtod(buffer, &temp);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_ldouble(long double *value, FILE *stream) {
    char buffer[BUF_SIZE], *temp;
    long double v;

    if (fget_input(buffer, BUF_SIZE, stream) == EOF)
        return EOF;

    errno = 0;
    v = strtold(buffer, &temp);

    if (errno != 0 || temp == buffer || *temp != '\0')
        return FAILURE;
    else {
        *value = v;
        return SUCCESS;
    }
}


int fget_line(char *s, int len, FILE *stream) {
    if (fgets(s, len, stream) == NULL)
        return EOF;

    if (strchr(s, '\n') == NULL) {
        int ch;
        while ((ch = fgetc(stream)) != '\n' && ch != EOF);
    }

    return SUCCESS;
}


int get_short(short *value) {
    return fget_short(value, stdin);
}

int get_ushort(unsigned short *value) {
    return fget_ushort(value, stdin);
}

int get_int(int *value) {
    return fget_int(value, stdin);
}


int get_uint(unsigned int *value) {
    return fget_uint(value, stdin);
}


int get_long(long *value) {
    return fget_long(value, stdin);
}


int get_ulong(unsigned long *value) {
    return fget_ulong(value, stdin);
}


int get_llong(long long *value) {
    return fget_llong(value, stdin);
}


int get_ullong(unsigned long long *value) {
    return fget_ullong(value, stdin);
}

int get_float(float *value) {
    return fget_float(value, stdin);
}

int get_double(double *value) {
    return fget_double(value, stdin);
}

int get_ldouble(long double *value) {
    return fget_ldouble(value, stdin);
}

int get_line(char *s, int len) {
    return fget_line(s, len, stdin);
}

