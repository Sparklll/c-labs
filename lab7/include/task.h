#ifndef TASK_H
#define TASK_H

#include <time.h>
#include "list.h"

typedef struct tm date;

typedef struct task {
    char task_name[128];
    int duration_in_days;
    date task_begin;
    date task_end;
    list *assigned_resources;
} task;

task *create_task();

void print_task(task *task);

void edit_task(task *task);

void set_task_name(task *task);

void set_task_begin_date(task *task);

void set_task_duration(task *task);

void delete_task(task *task);

#endif