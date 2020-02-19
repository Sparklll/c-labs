#include <stdio.h>
#include "order_control.h"
#include "input validation/smartinput.h"


int main() {
    int i = 1;
    while (i) {
        double cargo_weight;
        double distance;

        printf("Enter the cargo weight : ");
        while (get_double(&cargo_weight) != 0) {
            printf("Incorrect input, try again : ");
        }
        printf("Enter the distance : ");
        while (get_double(&distance) != 0) {
            printf("Incorrect input, try again : ");
        }
        if(data_analyze(cargo_weight, distance, 15, 20) == 0) {
            printf("Order has been refused");
        }
        printf("\nIf you want to continue press 1 otherwise 0 : ");
        while (get_int(&i) != 0) {
            printf("Incorrect input, try again : ");
        }
    }
    printf("\n\nVersion 1.0\nDeveloped by Eugene Gromadko");
    return 0;
}