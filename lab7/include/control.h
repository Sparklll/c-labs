#ifndef CONTROL_H
#define CONTROL_H

void main_menu();

void print_program_logo();

void clear_console();

void clear_input_buffer();

int date_validation(int *ptr_day, int *ptr_month, int *ptr_year);

int __getch();

#endif