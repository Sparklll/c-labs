#ifdef __GNUC__
#include <unistd.h>
#elif _WIN32
#include<Windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/queue.h"
#include "../include/military_commissariat.h"


int main() {
    srand(time(0));

    military_commissariat *military_commissariat = create_military_commissariat(5);
    int overall_conscripts_number = 10; /* Test number of conscripts */
    int conscripts_finished_examination = 0;
    int current_room_spent_time[overall_conscripts_number];

    conscript *conscripts[overall_conscripts_number];
    int i;
    for (i = 0; i < overall_conscripts_number; i++) {
        conscripts[i] = create_conscript(i);
    }

    int ticks = 0;
    while (conscripts_finished_examination != overall_conscripts_number) {

        int j;
        for (j = 0; j < overall_conscripts_number; j++) {
            if (conscripts[j]->random_entry_commissariat_time == ticks) {
                enter_medical_room(military_commissariat, conscripts[j]);
                current_room_spent_time[j] = rand() % 5 + 1; /* Test waiting time in the medical room in range [1..5] */
            }
        }

        for (j = 0; j < military_commissariat->num_medical_rooms; j++) {
            queue *current_queue = military_commissariat->medical_rooms[j];
            if (current_queue->front != NULL) {
                conscript *front_conscript = current_queue->front->data;

                if (current_room_spent_time[front_conscript->personal_number] ==
                    front_conscript->last_medical_room_time_spent) {
                    front_conscript->total_time_spent += front_conscript->last_medical_room_time_spent;
                    left_medical_room(military_commissariat, front_conscript, j,
                                      current_room_spent_time[front_conscript->personal_number]);
                    if (front_conscript->num_visited_rooms < military_commissariat->num_medical_rooms) {
                        front_conscript->last_medical_room_time_spent = 0;
                        current_room_spent_time[front_conscript->personal_number] =
                                rand() % 5 + 1; /* Test waiting time in the medical room in range [1..5] */
                        enter_medical_room(military_commissariat, front_conscript);
                    } else {
                        conscripts_finished_examination++;
                    }
                }
                front_conscript->last_medical_room_time_spent++;
            }
        }

        sleep(1);
        ticks++;
    }


    for (i = 0; i < overall_conscripts_number; i++) {
        delete_conscript(conscripts[i]);
    }
    delete_military_commissariat(military_commissariat);
    return 0;
}
