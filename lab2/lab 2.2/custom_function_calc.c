#include "custom_function_calc.h"


long double factorial(int n) {
    if (n == 0) {
        return 1;
    } else return n * factorial(n - 1);
}

long double iterative_calc(double x, double precision, int *num_members) {
    long double sum = 0;
    int i = 1, k;

    while (fabsl(sin(x) - sum) > precision) {
        k = (i - 1) % 2 == 0 ? 1 : -1;
        sum += k * powl(x, 2 * i - 1) / factorial(2 * i - 1);
        i++;
    }
    *num_members = i;
    return sum;
}

/*
long double recursive_calc(double x, int num_members) {
    if (num_members >= 1) {
        return function(x, num_members) + recursive_calc(x, num_members - 1);
    }
    return 0;
}

long double function(double x, int n) {
    return powl(-1, n - 1) * (powl(x, 2 * n - 1) / factorial(2 * n - 1));
}
*/





