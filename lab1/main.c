#include <stdio.h>
#include "sfractional.h"
#include "input validation/smartinput.h"


int main() {
    double number;
    int n;

    printf("Enter the real number : ");
    while (get_double(&number) != 0) {
        printf("Incorrect input, try again : ");
    }

    printf("Enter the number of first digits of the fractional part of the real number the amount of which you want to calculate : ");
    while (get_int(&n) != 0) {
        printf("Incorrect input, try again : ");
    }

    printf("The sum of the first %i digits of the fractional part of a real number is %i", n,
           fractional_digit_sum(number, n));

}

