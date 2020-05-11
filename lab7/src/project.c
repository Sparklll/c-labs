#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/control.h"
#include "../include/project.h"
#include "../include/task.h"
#include "../include/resource.h"
#include "../include/smartinput.h"

project *create_project() {
    project *project = malloc(sizeof(struct project));
    project->tasks = create_list(sizeof(struct task));
    project->resources = create_list(sizeof(struct resource));

    strcpy(project->project_name, "DEFAULT PROJECT NAME");
    strcpy(project->project_currency, "($) U.S. dollar");
    project->working_hours_per_day = 8;

    print_program_logo();
    puts("Would you like to carry out basic setup of the project? (Y/n)");

    int isEnd = 0;
    while (!isEnd) {
        int answer = tolower(__getch());

        if (answer == 'y') {
            isEnd = 1;
            basic_project_setup(project);
        } else if (answer == 'n') {
            isEnd = 1;
        }
    }

    return project;
}

project *open_project() {
    int escape = 0;
    while (!escape) {
        print_program_logo();
        printf("Enter project file_name (stored in \"projects\" folder) : ");
        char full_file_path[128] = "../projects/";
        char file_name[128];

        fgets(file_name, 128, stdin);
        file_name[strlen(file_name) - 1] = 0;
        strcat(full_file_path, file_name);
        strcat(full_file_path, ".proj");

        project *project;
        FILE *project_file = fopen(full_file_path, "rb");
        int success = 0;

        if (project_file != NULL) {
            project = malloc(sizeof(struct project));
            project->tasks = create_list(sizeof(struct task));
            project->resources = create_list(sizeof(struct resource));

            size_t num_of_tasks = 0;
            size_t num_of_resources = 0;

            fread(project->project_name, sizeof(char), 128, project_file); /* Project name */
            fread(project->project_currency, sizeof(char), 32, project_file); /* Project currency */
            fread(&project->working_hours_per_day, sizeof(int), 1, project_file); /* Project working h p/d */
            fread(&num_of_tasks, sizeof(size_t), 1, project_file); /* Number of project tasks */

            int i;
            for (i = 0; i < num_of_tasks; i++) { /* Loading project Tasks */
                task *temp_task = malloc(sizeof(struct task));
                temp_task->assigned_resources = create_list(sizeof(struct resource));

                size_t temp_num_of_assigned_resources = 0;

                fread(temp_task->task_name, sizeof(char), 128, project_file); /* Task name */
                fread(&temp_task->duration_in_days, sizeof(int), 1, project_file); /* Task duration */
                fread(&temp_task->task_begin, sizeof(struct tm), 1, project_file); /* Task begin date */
                fread(&temp_task->task_end, sizeof(struct tm), 1, project_file); /* Task end date */
                fread(&temp_num_of_assigned_resources, sizeof(size_t), 1, project_file); /* Task size of resources */

                list_push_back(project->tasks, temp_task);
                task *last_added_task = project->tasks->tail->data;
                last_added_task->assigned_resources = create_list(sizeof(struct resource));
                delete_task(temp_task);

                int j;
                for (j = 0; j < temp_num_of_assigned_resources; j++) {
                    resource *temp_resource = malloc(sizeof(struct resource));

                    fread(temp_resource->resource_name, sizeof(char), 128, project_file); /* Task resource name */
                    fread(&temp_resource->usage_costs, sizeof(int), 1, project_file); /* Task resource usage cost */
                    fread(&temp_resource->standard_rate, sizeof(int), 1, project_file); /* Task resource standart rate */

                    list_push_back(last_added_task->assigned_resources, temp_resource);
                    delete_resource(temp_resource);
                }
            }

            fread(&num_of_resources, sizeof(size_t), 1, project_file); /* Number of project resources */

            int j;
            for (j = 0; j < num_of_resources; j++) { /* Loading project Resources */
                resource *temp_resource = malloc(sizeof(struct resource));

                fread(temp_resource->resource_name, sizeof(char), 128, project_file); /* Resource name */
                fread(&temp_resource->usage_costs, sizeof(int), 1, project_file); /* Resource usage cost */
                fread(&temp_resource->standard_rate, sizeof(int), 1, project_file); /* Resource standart rate */

                list_push_back(project->resources, temp_resource);
                delete_resource(temp_resource);
            }

            puts("Project successfully opened!");
            success = 1;
        } else {
            puts("WARNING : file open error!");
        }
        puts("\n\n<ESC> BACK\t<PRESS ANY KEY TO REPEAT>");
        int lever = __getch();

        switch (lever) {
            case 27 : { /* ESC press case */
                if (success) {
                    fclose(project_file);
                    return project;
                } else {
                    return NULL;
                    break;
                }
            }
        }
    }
}

void save_project(project *project) {
    int escape = 0;
    while (!escape) {
        print_program_logo();


        printf("Enter the file_name in which you want to save project : ");
        char full_file_path[128] = "../projects/";
        char file_name[128];
        fgets(file_name, 128, stdin);
        file_name[strlen(file_name) - 1] = 0;
        strcat(full_file_path, file_name);
        strcat(full_file_path, ".proj");


        FILE *project_file = fopen(full_file_path, "wb");
        fwrite(project->project_name, sizeof(char), 128, project_file); /* Project name */
        fwrite(project->project_currency, sizeof(char), 32, project_file); /* Project currency */
        fwrite(&project->working_hours_per_day, sizeof(int), 1, project_file); /* Project working h p/d */
        fwrite(&project->tasks->size, sizeof(size_t), 1, project_file); /* Number of project tasks */

        list_node *temp_task_node = project->tasks->head;
        while (temp_task_node != NULL) { /* Saving project Tasks */
            task *temp_task = temp_task_node->data;
            fwrite(temp_task->task_name, sizeof(char), 128, project_file); /* Task name */
            fwrite(&temp_task->duration_in_days, sizeof(int), 1, project_file); /* Task duration */
            fwrite(&temp_task->task_begin, sizeof(struct tm), 1, project_file); /* Task begin date */
            fwrite(&temp_task->task_end, sizeof(struct tm), 1, project_file); /* Task end date */
            fwrite(&temp_task->assigned_resources->size, sizeof(size_t), 1, project_file); /* Task size of resources */

            list_node *temp_resource_node = temp_task->assigned_resources->head;
            while (temp_resource_node != NULL) {
                resource *temp_resource = temp_resource_node->data;
                fwrite(temp_resource->resource_name, sizeof(char), 128, project_file); /* Task resource name */
                fwrite(&temp_resource->usage_costs, sizeof(int), 1, project_file); /* Task resource usage cost */
                fwrite(&temp_resource->standard_rate, sizeof(int), 1, project_file); /* Task resource standart rate */
                temp_resource_node = temp_resource_node->next;
            }

            temp_task_node = temp_task_node->next;
        }

        fwrite(&project->resources->size, sizeof(size_t), 1, project_file); /* Number of project resources */
        list_node *temp_resource_node = project->resources->head;
        while (temp_resource_node != NULL) { /* Saving project Resources */
            resource *temp_resource = temp_resource_node->data;
            fwrite(temp_resource->resource_name, sizeof(char), 128, project_file); /* Resource name */
            fwrite(&temp_resource->usage_costs, sizeof(int), 1, project_file); /* Resource usage cost */
            fwrite(&temp_resource->standard_rate, sizeof(int), 1, project_file); /* Resource standart rate */

            temp_resource_node = temp_resource_node->next;
        }

        fclose(project_file);
        puts("Project successfully saved!");
        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void remove_project(project *project) {
    list_node *temp_node = project->tasks->head;

    while (temp_node != NULL) {
        task *temp_task = temp_node->data;
        delete_task(temp_task);

        temp_node = temp_node->next;
    }

    temp_node = project->resources->head;
    while (temp_node != NULL) {
        resource *temp_resource = temp_node->data;
        delete_resource(temp_resource);

        temp_node = temp_node->next;
    }

    free(project->tasks);
    free(project->resources);
    free(project);
}

void basic_project_setup(project *project) {
    int escape = 0;
    while (!escape) {
        print_program_logo();
        puts(">>BASIC PROJECT SETUP MENU<<\n");

        printf("PROJECT NAME : %s\n", project->project_name);
        printf("PROJECT CURRENCY : %s\n", project->project_currency);
        printf("PROJECT WORKING HOURS PER DAY : %d\n\n\n", project->working_hours_per_day);
        puts("1. Edit project name");
        puts("2. Edit project currency");
        puts("3. Edit project working hours per day");
        puts("\n\n<ESC> FINISH SETUP");

        int lever = __getch();

        switch (lever) {
            case '1' : {
                set_project_name(project);
                break;
            }
            case '2': {
                set_project_currency(project);
                break;
            }
            case '3': {
                set_project_working_hours_per_day(project);
                break;
            }
            case 27: { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void set_project_name(project *project) {
    print_program_logo();
    printf("Enter project name : ");
    fgets(project->project_name, 128, stdin);
    int wordLength = strlen(project->project_name);
    project->project_name[wordLength - 1] = 0;
}

void set_project_currency(project *project) {
    print_program_logo();
    printf("Enter project currency : ");
    fgets(project->project_currency, 32, stdin);
    int wordLength = strlen(project->project_currency);
    project->project_currency[wordLength - 1] = 0;
}

void set_project_working_hours_per_day(project *project) {
    int hours;
    int isCorrect = 0;

    while (!isCorrect) {
        print_program_logo();
        printf("Enter project working hours per day (1-24): ");

        if (get_int(&hours) == SUCCESS && (hours > 0 && hours <= 24)) {
            isCorrect = 1;
        }
    }
    project->working_hours_per_day = hours;
}

void project_menu(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);

        puts(">>PROJECT MENU<<");
        puts("1. Task menu");
        puts("2. Resource menu");
        puts("3. Project calculation menu");
        puts("4. Basic project setup menu");
        puts("5. Save project");
        puts("\n\n<ESC> MAIN MENU");
        int lever = __getch();

        switch (lever) {
            case '1' : {
                tasks_setup(project);
                break;
            }
            case '2' : {
                resources_setup(project);
                break;
            }
            case '3' : {
                project_calculation_menu(project);
                break;
            }
            case '4' : {
                basic_project_setup(project);
                break;
            }
            case '5' : {
                save_project(project);
                break;
            }
            case 27 : { /* ESC press case */
                print_project_header(project);

                puts("Would you like to save your project (Y/n)?");
                int isEnd = 0;

                while (!isEnd) {
                    int answer = tolower(__getch());

                    if (answer == 'y') {
                        isEnd = 1;
                        save_project(project);
                    } else if (answer == 'n') {
                        isEnd = 1;
                        remove_project(project);
                    }
                }
                escape = 1;
                break;
            }
        }
    }
}

void tasks_setup(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);

        puts(">>TASK SETUP MENU<<");
        puts("1. Display a list of tasks");
        puts("2. Edit task");
        puts("3. Add task");
        puts("4. Remove task");
        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case '1' : {
                display_project_tasks(project);
                break;
            }
            case '2' : {
                int local_escape = 0;
                while (!local_escape) {
                    print_project_header(project);

                    printf("Enter the index of the task (from task list) you want to edit : ");
                    int task_index;
                    if (get_int(&task_index) == SUCCESS && (task_index >= 0 && task_index < project->tasks->size)) {
                        list_node *temp_node = get_list_element(project->tasks, task_index);
                        edit_task(temp_node->data);
                        print_project_header(project);
                        puts("\nSuccessfully edited!");
                    } else {
                        print_project_header(project);
                        puts("\nWARNING : invalid task index!");
                    }
                    puts("\n\n<ESC> BACK\t<ENTER> CONTINUE EDITING");

                    int isEnd = 0;
                    while (!isEnd) {
                        int local_lever = __getch();
                        switch (local_lever) {
                            #ifdef _WIN32
                            case 13
                            #elif __GNUC__
                            case 10
                            #endif
                                : { /* ENTER press case */
                                isEnd = 1;
                                break;
                            }
                            case 27 : { /* ESC press case */
                                isEnd = 1;
                                local_escape = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case '3' : {
                add_project_task(project);
                break;
            }
            case '4' : {
                remove_project_task(project);
                break;
            }
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }

        }
    }
}

void display_project_tasks(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);
        puts(">>TASK LIST<<\n");

        list_node *temp_node = project->tasks->head;
        int counter = 0;

        while (temp_node != NULL) {
            printf("<Task #%d>\n", counter);
            print_task(temp_node->data);
            counter++;
            temp_node = temp_node->next;
        }

        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void add_project_task(project *project) {
    task *new_temp_task = create_task();

    int escape = 0;
    while (!escape) {
        print_project_header(project);
        print_task(new_temp_task);
        puts("\n\n<ENTER> SAVE TASK\t<ESC> CANCEL");
        int lever = __getch();

        switch (lever) {
            #ifdef _WIN32
            case 13
            #elif __GNUC__
            case 10
            #endif
                : { /* ENTER press case */
                list_push_back(project->tasks, new_temp_task);
                task *last_added_task = project->tasks->tail->data;
                last_added_task->assigned_resources = create_list(sizeof(struct resource));

                delete_task(new_temp_task);
                escape = 1;
                break;
            }
            case 27 : { /* ESC press case */
                delete_task(new_temp_task);
                escape = 1;
                break;
            }
        }
    }
}

void remove_project_task(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);
        puts(">>REMOVE PROJECT TASK<<\n");
        printf("Enter the index of the task (from task list) you want to delete : ");

        int task_index;
        if (get_int(&task_index) == SUCCESS && (task_index >= 0 && task_index < project->tasks->size)) {
            list_pop(project->tasks, task_index);
            puts("\nSuccessfully removed!");
        } else {
            puts("\nWARNING : invalid task index!");
        }
        puts("\n\n<ESC> BACK\t<ENTER> CONTINUE REMOVING");

        int isEnd = 0;
        while (!isEnd) {
            int lever = __getch();
            switch (lever) {
                #ifdef _WIN32
                case 13
                #elif __GNUC__
                case 10
                #endif
                    : { /* ENTER press case */
                    isEnd = 1;
                    break;
                }
                case 27 : { /* ESC press case */
                    isEnd = 1;
                    escape = 1;
                    break;
                }
            }
        }
    }
}

void resources_setup(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);

        puts(">>RESOURCE SETUP MENU<<");
        puts("1. Display a list of resources");
        puts("2. Assign resources to the task");
        puts("3. Add resource");
        puts("4. Edit resource");
        puts("5. Remove resource");
        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case '1' : {
                display_project_resources(project);
                break;
            }
            case '2' : {
                int local_escape = 0;
                while (!local_escape) {
                    resource *resource_to_assign = NULL;
                    task *selected_task = NULL;

                    print_project_header(project);
                    printf("Enter the index of the resource (from resource list) you want to assign to the task : ");
                    int resource_index;
                    if (get_int(&resource_index) == SUCCESS &&
                        (resource_index >= 0 && resource_index < project->resources->size)) {
                        resource_to_assign = get_list_element(project->resources, resource_index)->data;

                    }

                    print_project_header(project);
                    printf("Enter the index of the task (from task list) for which you want to assign the resource : ");
                    int task_index;
                    if (get_int(&task_index) == SUCCESS &&
                        (task_index >= 0 && task_index < project->tasks->size)) {
                        selected_task = get_list_element(project->tasks, task_index)->data;
                    }

                    if (resource_to_assign != NULL && selected_task != NULL) {
                        assign_resource(resource_to_assign, selected_task);

                        print_project_header(project);
                        printf("Resource <%s> successfully assigned to the task <%s>",
                               resource_to_assign->resource_name, selected_task->task_name);
                    } else {
                        print_project_header(project);
                        puts("\nWARNING : invalid resource or task index!");
                    }
                    puts("\n\n<ESC> BACK\t<ENTER> CONTINUE EDITING");

                    int isEnd = 0;
                    while (!isEnd) {
                        int local_lever = __getch();
                        switch (local_lever) {
                            #ifdef _WIN32
                            case 13
                            #elif __GNUC__
                            case 10
                            #endif
                                : { /* ENTER press case */
                                isEnd = 1;
                                break;
                            }
                            case 27 : { /* ESC press case */
                                isEnd = 1;
                                local_escape = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case '3' : {
                add_project_resource(project);
                break;
            }
            case '4' : {
                int local_escape = 0;
                while (!local_escape) {
                    print_project_header(project);

                    printf("Enter the index of the resource (from resource list) you want to edit : ");
                    int resource_index;
                    if (get_int(&resource_index) == SUCCESS &&
                        (resource_index >= 0 && resource_index < project->resources->size)) {
                        list_node *temp_node = get_list_element(project->resources, resource_index);
                        edit_resource(temp_node->data);
                        print_project_header(project);
                        puts("\nSuccessfully edited!");
                    } else {
                        print_project_header(project);
                        puts("\nWARNING : invalid resource index!");
                    }
                    puts("\n\n<ESC> BACK\t<ENTER> CONTINUE EDITING");

                    int isEnd = 0;
                    while (!isEnd) {
                        int local_lever = __getch();
                        switch (local_lever) {
                            #ifdef _WIN32
                            case 13
                            #elif __GNUC__
                            case 10
                            #endif
                                : { /* ENTER press case */
                                isEnd = 1;
                                break;
                            }
                            case 27 : { /* ESC press case */
                                isEnd = 1;
                                local_escape = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case '5' : {
                remove_project_resource(project);
                break;
            }
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }

        }
    }
}

void display_project_resources(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);
        puts(">>RESOURCE LIST<<\n");

        list_node *temp_node = project->resources->head;
        int counter = 0;

        while (temp_node != NULL) {
            printf("<RESOURCE #%d>\n", counter);
            print_resource(temp_node->data);
            counter++;
            temp_node = temp_node->next;
        }

        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void add_project_resource(project *project) {
    resource *new_temp_resource = create_resource();

    int escape = 0;
    while (!escape) {
        print_project_header(project);
        print_resource(new_temp_resource);
        puts("\n\n<ENTER> SAVE RESOURCE\t<ESC> CANCEL");
        int lever = __getch();

        switch (lever) {
            #ifdef _WIN32
            case 13
            #elif __GNUC__
            case 10
            #endif
                : { /* ENTER press case */
                list_push_back(project->resources, new_temp_resource);
                delete_resource(new_temp_resource);
                escape = 1;
                break;
            }
            case 27 : { /* ESC press case */
                delete_resource(new_temp_resource);
                escape = 1;
                break;
            }
        }
    }
}

void assign_resource(resource *resource, task *task) {
    list_push_back(task->assigned_resources, resource);
}

void remove_project_resource(project *project) {
    int escape = 0;
    while (!escape) {
        print_project_header(project);
        puts(">>REMOVE PROJECT RESOURCE<<\n");
        printf("Enter the index of the resource (from resource list) you want to delete : ");

        int resource_index;
        if (get_int(&resource_index) == SUCCESS && (resource_index >= 0 && resource_index < project->resources->size)) {
            list_pop(project->resources, resource_index);
            puts("\nSuccessfully removed!");
        } else {
            puts("\nWARNING : invalid resource index!");
        }
        puts("\n\n<ESC> BACK\t<ENTER> CONTINUE REMOVING");

        int isEnd = 0;
        while (!isEnd) {
            int lever = __getch();
            switch (lever) {
                #ifdef _WIN32
                case 13
                #elif __GNUC__
                case 10
                #endif
                    : { /* ENTER press case */
                    isEnd = 1;
                    break;
                }
                case 27 : { /* ESC press case */
                    isEnd = 1;
                    escape = 1;
                    break;
                }
            }
        }
    }
}

void print_project_header(project *project) {
    print_program_logo();
    printf("CURRENT PROJECT : <%s>\n\n\n", project->project_name);
}

void project_calculation_menu(project *project) {
    int escape = 0;
    while (!escape) {
        print_program_logo();

        puts(">>PROJECT CALCULATIONS<<\n");
        display_project_calculations(project);
        puts("\n\n<ESC> BACK");
        int lever = __getch();

        switch (lever) {
            case 27 : { /* ESC press case */
                escape = 1;
                break;
            }
        }
    }
}

void display_project_calculations(project *project) {
    date project_begin_date;
    date project_end_date;
    double total_project_cost = 0;

    printf("Current project : <%s>\n", project->project_name);
    printf("Assigned tasks on the project : <%zu>\n", project->tasks->size);
    printf("Assigned resources on the project : <%zu>\n", project->resources->size);
    if (project->tasks->size > 0) {
        list_node *temp_node = project->tasks->head;
        task *temp_task = temp_node->data;
        project_begin_date = temp_task->task_begin;
        project_end_date = temp_task->task_end;

        while (temp_node != NULL) {
            temp_task = temp_node->data;
            if (mktime(&temp_task->task_begin) < mktime(&project_begin_date)) {
                project_begin_date = temp_task->task_begin;
            }
            if (mktime(&temp_task->task_end) > mktime(&project_end_date)) {
                project_end_date = temp_task->task_end;
            }

            list_node *temp_resource_node = temp_task->assigned_resources->head;
            while (temp_resource_node != NULL) {
                resource *temp_resource = temp_resource_node->data;
                total_project_cost += temp_resource->usage_costs;
                total_project_cost +=
                        temp_resource->standard_rate * temp_task->duration_in_days * project->working_hours_per_day;
                temp_resource_node = temp_resource_node->next;
            }

            temp_node = temp_node->next;
        }

        printf("Project start date : %d/%d/%d\n",
               project_begin_date.tm_mday,
               project_begin_date.tm_mon + 1,
               project_begin_date.tm_year + 1900);
        printf("Project end date : %d/%d/%d\n",
               project_end_date.tm_mday,
               project_end_date.tm_mon + 1,
               project_end_date.tm_year + 1900);
    }
    printf("Total project cost : %f %s\n", total_project_cost, project->project_currency);
}
