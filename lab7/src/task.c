#include <stdio.h>
#include <string.h>
#include "../include/task.h"
#include "../include/resource.h"
#include "../include/control.h"
#include "../include/smartinput.h"

task *create_task() {
    task *task = malloc(sizeof(struct task));
    task->assigned_resources = create_list(sizeof(struct resource));

    set_task_name(task);
    set_task_begin_date(task);
    set_task_duration(task);

    return task;
}

void print_task(task *task) {
    printf("Task name : %s\n", task->task_name);
    printf("Task begin date : %d/%d/%d\n",
           task->task_begin.tm_mday,
           task->task_begin.tm_mon + 1,
           task->task_begin.tm_year + 1900);
    printf("Task end date : %d/%d/%d\n",
           task->task_end.tm_mday,
           task->task_end.tm_mon + 1,
           task->task_end.tm_year + 1900);
    printf("Total task duration : %d days\n", task->duration_in_days);
    printf("Task resources : [");

    list_node *temp_node = task->assigned_resources->head;
    while (temp_node != NULL) {
        resource *temp_resourse = temp_node->data;
        printf("%s, ", temp_resourse->resource_name);
        temp_node = temp_node->next;
    }
    printf("]\n\n");
}

void edit_task(task *task) {
    int escape = 0;
    while (!escape) {
        print_program_logo();
        puts(">>EDIT TASK MENU<<\n");
        puts("<TASK>");
        print_task(task);

        puts("1. Edit task name");
        puts("2. Edit task begin date");
        puts("3. Edit task duration");
        puts("4. Edit task resources");
        puts("\n\n<ESC> FINISH SETUP");

        int lever = __getch();

        switch (lever) {
            case '1' : {
                set_task_name(task);
                break;
            }
            case '2': {
                set_task_begin_date(task);
                task->task_end = task->task_begin;
                task->task_end.tm_mday += task->duration_in_days;
                mktime(&task->task_end);
                break;
            }
            case '3': {
                set_task_duration(task);
                break;
            }
            case 27: { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void set_task_name(task *task) {
    print_program_logo();
    printf("Enter task name : ");
    fgets(task->task_name, 128, stdin);
    int wordLength = strlen(task->task_name);
    task->task_name[wordLength - 1] = 0;
}

void set_task_begin_date(task *task) {
    int isCorrect = 0;
    while (!isCorrect) {
        print_program_logo();
        int day, month, year;

        printf("Enter task begin date (DD/MM/YYYY): ");
        int flag = date_validation(&day, &month, &year);
        clear_input_buffer();

        if (flag == 1) {
            isCorrect = 1;

            task->task_begin.tm_mday = day;
            task->task_begin.tm_mon = month - 1;
            task->task_begin.tm_year = year - 1900;
        }
    }
}

void set_task_duration(task *task) {
    int isCorrect = 0;
    while (!isCorrect) {
        print_program_logo();
        int days;
        printf("Enter task duration (days) : ");

        if (get_int(&days) == SUCCESS && days >= 0) {
            isCorrect = 1;
            task->duration_in_days = days;
            task->task_end = task->task_begin;
            task->task_end.tm_mday += days;
            mktime(&task->task_end);
        }
    }
}

void delete_task(task *task) {
    delete_list(task->assigned_resources);
    free(task);
}
