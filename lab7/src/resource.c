#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/resource.h"
#include "../include/control.h"
#include "../include/smartinput.h"


resource *create_resource() {
    resource *resource = malloc(sizeof(struct resource));

    set_resource_name(resource);
    set_resource_usage_cost(resource);
    set_resource_standart_rate(resource);

    return resource;
}

void print_resource(resource *resource) {
    printf("Resource name : %s\n", resource->resource_name);
    printf("Resource usage cost : %d\n", resource->usage_costs);
    printf("Resource standart rate (per hour) : %d\n\n", resource->standard_rate);
}

void edit_resource(resource *resource) {
    int escape = 0;
    while (!escape) {
        print_program_logo();
        puts(">>EDIT RESOURCE MENU<<\n");
        puts("<RESOURCE>");
        print_resource(resource);

        puts("1. Edit resource name");
        puts("2. Edit resource usage cost");
        puts("3. Edit resource standart rate (per hour)");
        puts("\n\n<ESC> FINISH SETUP");

        int lever = __getch();

        switch (lever) {
            case '1' : {
                set_resource_name(resource);
                break;
            }
            case '2': {
                set_resource_usage_cost(resource);
                break;
            }
            case '3': {
                set_resource_standart_rate(resource);
                break;
            }
            case 27: { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void set_resource_name(resource *resource) {
    print_program_logo();
    printf("Enter resource name : ");
    fgets(resource->resource_name, 128, stdin);
    int wordLength = strlen(resource->resource_name);
    resource->resource_name[wordLength - 1] = 0;
}

void set_resource_usage_cost(resource *resource) {
    int isCorrect = 0;
    while (!isCorrect) {
        print_program_logo();
        int usage_costs;

        printf("Enter resource usage costs : ");

        if (get_int(&usage_costs) == SUCCESS && usage_costs >= 0) {
            isCorrect = 1;
            resource->usage_costs = usage_costs;
        }
    }
}

void set_resource_standart_rate(resource *resource) {
    int isCorrect = 0;
    while (!isCorrect) {
        print_program_logo();
        int standart_rate;

        printf("Enter resource standart rate (per hour) : ");

        if (get_int(&standart_rate) == SUCCESS && standart_rate >= 0) {
            isCorrect = 1;
            resource->standard_rate = standart_rate;
        }
    }
}

void delete_resource(resource *resource) {
    free(resource);
}
