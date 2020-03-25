#include <stdlib.h>
#include "cube.h"


void cube_initialization(cube *cube, FILE *input_file) {
    int side_length;
    char buffer[BUF_SIZE];
    char waste_buffer[BUF_SIZE];


    fgets(buffer, BUF_SIZE, input_file);
    fgets(waste_buffer, BUF_SIZE, input_file); /* empty line */
    side_length = (int) strtol(buffer, NULL, 10);
    cube->side_length = side_length;
    cube->cube_array = malloc(side_length * sizeof(int **));
    int z;
    for (z = 0; z < side_length; z++) {
        cube->cube_array[z] = malloc(side_length * sizeof(int *));
        int y;
        for (y = 0; y < side_length; y++) {
            cube->cube_array[z][y] = malloc(side_length * sizeof(int));
        }
    }

    /* filling cube */
    for (z = 0; z < side_length; z++) {
        int y;
        for (y = 0; y < side_length; y++) {
            fgets(buffer, BUF_SIZE, input_file);
            int x;
            for (x = 0; x < side_length; x++) {
                cube->cube_array[z][y][x] = buffer[x] - '0';
            }
        }

        fgets(waste_buffer, BUF_SIZE, input_file); /* empty line */

    }
}

void cube_release(cube *cube) {
    int side_length = cube->side_length;

    int z;
    for (z = 0; z < side_length; z++) {
        int y;
        for (y = 0; y < side_length; y++) {
            free(cube->cube_array[z][y]);
        }
        free(cube->cube_array[z]);
    }
    free(cube->cube_array);
}

void cube_analyze(cube *cube) {
    /* x-axis */
    int z;
    for (z = 0; z < cube->side_length; z++) {
        int y;
        for (y = 0; y < cube->side_length; y++) {
            int visible_elements = 0;
            int x;
            for (x = 0; x < cube->side_length; x++) {
                if (cube->cube_array[z][y][x]) {
                    visible_elements++;
                } else {
                    break;
                }
            }
            if (visible_elements == cube->side_length) {
                printf("visible segment : (*, %d, %d)\n", y + 1, z + 1);
            }
        }
    }

    /* y-axis */
    for (z = 0; z < cube->side_length; z++) {
        int x;
        for (x = 0; x < cube->side_length; x++) {
            int visible_elements = 0;
            int y;
            for (y = 0; y < cube->side_length; y++) {
                if (cube->cube_array[z][y][x]) {
                    visible_elements++;
                } else {
                    break;
                }
            }
            if (visible_elements == cube->side_length) {
                printf("visible segment : (%d, *, %d)\n", x + 1, z + 1);
            }
        }
    }

    /* z-axis */
    int y;
    for (y = 0; y < cube->side_length; y++) {
        int x;
        for (x = 0; x < cube->side_length; x++) {
            int visible_elements = 0;
            for (z = 0; z < cube->side_length; z++) {
                if (cube->cube_array[z][y][x]) {
                    visible_elements++;
                } else {
                    break;
                }
            }
            if (visible_elements == cube->side_length) {
                printf("visible segment : (%d, %d, *)\n", x + 1, y + 1);
            }
        }
    }
}
