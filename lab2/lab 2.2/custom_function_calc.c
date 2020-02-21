#include "custom_function_calc.h"


double factorial(int n) {
    if (n == 0) {
        return 1;
    } else return n * factorial(n - 1);
}

double iterative_calc(double x, double precision, int *num_members) {
    double sum = 0;
    double period = 2 * M_PI;
    int i = 1, k;

    if (x > 0) {
        while (x > period) {
            x -= period;
        }
    } else {
        while (x < period) {
            x += period;
        }
    }

    while (fabs(sin(x) - sum) > precision) {
        k = (i - 1) % 2 == 0 ? 1 : -1;
        sum += k * pow(x, 2 * i - 1) / factorial(2 * i - 1);
        i++;
    }
    *num_members = i;
    return sum;
}





