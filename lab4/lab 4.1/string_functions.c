#include <stdio.h>
#include <string.h>
#include "string_functions.h"

int check_if_string_periodic(char *string) {
    char double_string[BUF_SIZE];
    int string_length = (int) strlen(string);

    if (string_length > 1) {

        /* make double string */
        strcpy(double_string, string);
        strcat(double_string, string);

        int i;
        for (i = 1; i < string_length / 2 + 1; i++) {
            char temp_buffer[BUF_SIZE];
            int j;
            for (j = 0; j < string_length; j++) {
                temp_buffer[j] = double_string[j + i];
            }
            temp_buffer[j] = '\0';
            if (strcmp(string, temp_buffer) == 0) {
                return i;
            }
        }
    }
    return 0;

}
