cmake_minimum_required(VERSION 3.15)

project(lab1 C)

set(CMAKE_C_STANDARD 90)

add_executable(lab1
        main.c
        sfractional.c
        sfractional.h
        "input validation/smartinput.c"
        "input validation/smartinput.h"
)
target_link_libraries(lab1 m)






