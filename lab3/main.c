#include <stdio.h>
#include <stdlib.h>
#include "cube.h"


int main() {
    FILE *stream = fopen("../input.txt", "r");
    if(stream ==    NULL){
        puts("Unable to open file.");
        return 1;
    }
    cube test_cube;
    cube_initialization(&test_cube, stream);
    cube_analyze(&test_cube);
    fclose(stream);
    cube_release(&test_cube);
    return 0;
}
