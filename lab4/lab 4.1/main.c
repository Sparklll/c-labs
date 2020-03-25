#include <string.h>
#include <stdio.h>
#include "string_functions.h"

int main() {
    char buffer[BUF_SIZE];

    puts("Enter a string to check for periodicity : ");
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    int period = check_if_string_periodic(buffer);
    if (period) {
        printf("The string is periodic. Period length is %d\n", period);
    } else {
        puts("String isn't periodic.\n");
    }

    return 0;
}
