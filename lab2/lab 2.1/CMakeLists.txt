cmake_minimum_required(VERSION 3.15)
project(lab2 C)

set(CMAKE_C_STANDARD 90)

add_executable(lab2
        main.c
        "input validation/smartinput.c"
        "input validation/smartinput.h"
         order_control.c
         order_control.h)
#target_link_libraries(lab1 m)