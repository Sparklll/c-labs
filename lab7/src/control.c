#ifdef _WIN32
#include<Windows.h>
#include <conio.h>
#elif __GNUC__
#include <termios.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "../include/project.h"
#include "../include/control.h"

void print_program_logo() {
    clear_console();
    puts("******************************");
    puts("\tB-PROJECT v.1.0");
    puts("******************************\n\n");
}

void main_menu() {
    while (1) {
        print_program_logo();

        puts("\t   MAIN MENU");
        puts("1. Open an existing project");
        puts("2. Create new project");
        puts("3. Exit");
        int lever = __getch();

        switch (lever) {
            case '1': {
                clear_console();
                project *opened_project = open_project();
                if(opened_project != NULL) {
                    project_menu(opened_project);
                }
                break;
            }
            case '2': {
                clear_console();
                project *new_project = create_project();
                clear_console();
                project_menu(new_project);
                break;
            }
            case '3': {
                clear_console();
                exit(0);
            }
        }
    }
}

int date_validation(int *ptr_day, int *ptr_month, int *ptr_year) {
    scanf("%d/%d/%d", ptr_day, ptr_month, ptr_year);

    int isLeap = 0, isValid = 1;
    int day = *ptr_day;
    int month = *ptr_month;
    int year = *ptr_year;

    if ((year >= 1900 && year <= 9999) && (day >= 1 && day <= 31) && (month >= 1 && month <= 12)) {
        /* check whether year is a leap year */
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            isLeap = 1;
        }

        if (month == 2) {
            if (!isLeap && day > 28) {
                isValid = 0;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day == 31) {
                isValid = 0;
            }
        }
    } else {
        isValid = 0;
    }

    return isValid;
}

void clear_console() {
#ifdef _WIN32
    system("cls");
#elif __GNUC__
    system("clear");
#endif
}

int __getch() {
#ifdef _WIN32
    getch();
#elif __GNUC__
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
#endif
}

void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


