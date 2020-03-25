#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>

#define BUF_SIZE 256
typedef struct cube cube;

struct cube {
    int side_length;
    int ***cube_array;
};

void cube_initialization(cube *cube, FILE *input_file);

void cube_analyze(cube *cube);

void cube_release(cube *cube);


#endif