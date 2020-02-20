cmake_minimum_required(VERSION 3.15)
project(lab_2_2 C)

set(CMAKE_C_STANDARD 90)

add_executable(lab_2_2
        main.c
        custom_function_calc.c
        custom_function_calc.h
        "input validation/smartinput.h"
        "input validation/smartinput.c"
        )
target_link_libraries(lab_2_2 m)