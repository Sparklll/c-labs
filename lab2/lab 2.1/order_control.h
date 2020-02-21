#ifndef ORDER_CONTROL
#define ORDER_CONTROL

void order_calculation(double rate_per_kilometer, double insurance_expenses, double max_truck_load, double cargo_weight, double distance);

void details_output(int needed_trucks, double insurance_cost, double total_cost);

int data_analyze(double cargo_weight, double distance, int trucks, double max_truck_load);

#endif