#include <math.h>
#include "sfractional.h"


int fractional_digit_sum(double number, int n) {
    int digit_sum = 0;

    int integer_part = (int) (number * (pow(10, n)));
    int i;
    for (i = 0; i < n; i++) {
        if(integer_part == 0) {
            break;
        }
        digit_sum += integer_part % 10;
        integer_part /= 10;

    }
    return digit_sum;
}











