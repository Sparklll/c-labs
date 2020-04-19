#include <stdlib.h>
#include <stdio.h>
#include "../include/conscript.h"

conscript *create_conscript(int personal_number) {
    conscript *conscript = malloc(sizeof(struct conscript));
    conscript->personal_number = personal_number;
    conscript->num_visited_rooms = 0;
    conscript->total_time_spent = 0;
    conscript->last_medical_room_time_spent = 0;
    conscript->random_entry_commissariat_time = rand() % 10 + 1; /* E.g random entry time */
    int i;
    for (i = 0; i < 5; i++) {
        conscript->visited_medical_rooms[i] = 0;
    }

    return conscript;
}

void delete_conscript(conscript *conscript) {
    free(conscript);
}
