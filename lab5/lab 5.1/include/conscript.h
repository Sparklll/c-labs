#ifndef CONSCRIPT_H
#define CONSCRIPT_H

typedef struct conscript {
    int personal_number;
    int num_visited_rooms;
    int random_entry_commissariat_time;
    int total_time_spent;
    int last_medical_room_time_spent;
    int visited_medical_rooms[5];
} conscript;

conscript *create_conscript(int personal_number);

void delete_conscript(conscript *conscript);

#endif
