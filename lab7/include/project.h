#ifndef PROJECT_H
#define PROJECT_H

#include "list.h"
#include "resource.h"
#include "task.h"

typedef struct project {
    char project_name[128];
    char project_currency[32];
    int  working_hours_per_day;
    list *tasks;
    list *resources;
} project;

project *create_project();

project *open_project();

void save_project(project *project);

void remove_project(project *project);

void project_menu(project *project);

void basic_project_setup(project *project);

void set_project_name(project *project);

void set_project_currency(project *project);

void set_project_working_hours_per_day(project *project);

void tasks_setup(project *project);

void display_project_tasks(project *project);

void add_project_task(project *project);

void remove_project_task(project *project);

void resources_setup(project *project);

void display_project_resources(project *project);

void add_project_resource(project *project);

void assign_resource(resource *resource, task *task);

void remove_project_resource(project *project);

void project_calculation_menu(project *project);

void print_project_header(project *project);

void display_project_calculations(project *project);

#endif