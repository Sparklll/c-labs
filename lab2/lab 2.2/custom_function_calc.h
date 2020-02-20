#ifndef CUSTOM_FUNCTION_CALC
#define CUSTOM_FUNCTION_CALC

#include <math.h>

long double factorial(int n);

long double function(double x, int n);

long double iterative_calc(double x, double precision, int *num_members);

long double recursive_calc(double x, int num_members);

#endif