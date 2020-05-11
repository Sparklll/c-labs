#ifndef RESOURCE_H
#define RESOURCE_H

typedef struct resource {
    char resource_name[128];
    int usage_costs;
    int standard_rate;
} resource;

resource *create_resource();

void print_resource(resource *resource);

void edit_resource(resource *resource);

void set_resource_name(resource *resource);

void set_resource_usage_cost(resource *resource);

void set_resource_standart_rate(resource *resource);

void delete_resource(resource *resource);

#endif