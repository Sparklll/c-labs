#ifndef MILITARY_COMMISSARIAT_H
#define MILITARY_COMMISSARIAT_H

#include "../queue/queue.h"

typedef struct military_commissariat {
    int num_medical_rooms;
    queue **medical_rooms;
} military_commissariat;

military_commissariat *create_military_commissariat(int medical_rooms_number);

void delete_military_commissariat(military_commissariat *military_commissariat);

void enter_medical_room(military_commissariat *military_commissariat, conscript *conscript);

void left_medical_room(military_commissariat *military_commissariat, conscript *conscript, int medical_room_number,
                       int time_spent);

#endif