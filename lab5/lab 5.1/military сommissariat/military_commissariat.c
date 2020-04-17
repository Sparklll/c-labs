#include <stdlib.h>
#include <stdio.h>
#include "military_commissariat.h"

military_commissariat *create_military_commissariat(int medical_rooms_number) {
    military_commissariat *military_commissariat = malloc(sizeof(struct military_commissariat));
    military_commissariat->num_medical_rooms = medical_rooms_number;

    military_commissariat->medical_rooms = malloc(medical_rooms_number * sizeof(queue *));
    int i;
    for (i = 0; i < medical_rooms_number; i++) {
        military_commissariat->medical_rooms[i] = create_queue();
    }

    return military_commissariat;
}

void delete_military_commissariat(military_commissariat *military_commissariat) {
    int i;
    for (i = 0; i < military_commissariat->num_medical_rooms; i++) {
        delete_queue(military_commissariat->medical_rooms[i]);
    }
    free(military_commissariat->medical_rooms);
    free(military_commissariat);
}

void enter_medical_room(military_commissariat *military_commissariat, conscript *conscript) {
    if (conscript->num_visited_rooms == 0) {
        printf("Conscript#%d entered military commissariat.\n", conscript->personal_number);
    }

    /* Search for an unvisited medical room with the smallest queue */
    queue *selected_room;
    int selected_room_number;
    int i;
    for (i = 0; i < military_commissariat->num_medical_rooms; i++) {
        if (conscript->visited_medical_rooms[i] == 0) {
            selected_room = military_commissariat->medical_rooms[i];
            selected_room_number = i;
            break;
        }
    }
    for (i = 0; i < military_commissariat->num_medical_rooms; i++) {
        if (military_commissariat->medical_rooms[i]->size < selected_room->size &&
            conscript->visited_medical_rooms[i] == 0) {
            selected_room = military_commissariat->medical_rooms[i];
            selected_room_number = i;
        }
    }
    queue_push(selected_room, conscript);
    printf("Conscript#%d entered medical room №%d.\n", conscript->personal_number, selected_room_number);
}

void left_medical_room(military_commissariat *military_commissariat, conscript *conscript, int medical_room_number,
                       int time_spent) {
    queue_pop(military_commissariat->medical_rooms[medical_room_number]);
    conscript->num_visited_rooms++;
    conscript->visited_medical_rooms[medical_room_number] = 1;

    if (conscript->num_visited_rooms == military_commissariat->num_medical_rooms) {
        printf("Conscript#%d finished a medical examination. Total time spent %dm\n", conscript->personal_number,
               conscript->total_time_spent);
    } else {
        printf("Conscript#%d left medical room №%d. Time spent in the room %dm. Status : %d/%d.\n",
               conscript->personal_number,
               medical_room_number, time_spent, conscript->num_visited_rooms,
               military_commissariat->num_medical_rooms);
    }
}
