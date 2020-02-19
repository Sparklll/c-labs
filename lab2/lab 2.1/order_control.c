#include "stdio.h"
#include "order_control.h"

#define CONFIRM 1
#define REJECT 0

int data_analyze(double cargo_weight, double distance, int trucks_num, double max_truck_load) {
    double weight_per_truck = cargo_weight / trucks_num;
    if (cargo_weight >= 50 && weight_per_truck <= max_truck_load && distance <= 4000) {
        order_calculation(2, 5, 20, cargo_weight, distance);
        return CONFIRM;
    } else {
        return REJECT;
    }
}

void order_calculation(double rate_per_kilometer, double insurance_expenses, double max_truck_load, double cargo_weight,
                       double distance) {
    int needed_trucks = (int) (cargo_weight / max_truck_load);
    double transportation_cost = needed_trucks * rate_per_kilometer * distance;
    double insurance_cost = (transportation_cost * insurance_expenses) / 100;
    double total_cost = transportation_cost + insurance_cost;
    details_output(needed_trucks, insurance_cost, total_cost);
}

void details_output(int needed_trucks, double insurance_cost, double total_cost) {
    printf("\n\n\t\tCONFIRMED order");
    printf("\nOrder details:\ninvolved trucks - %d,\ninsurance cost - %0.2f$,\ntotal cost - %0.2f$.", needed_trucks, insurance_cost,
           total_cost);
}



