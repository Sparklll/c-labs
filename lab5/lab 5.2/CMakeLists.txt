cmake_minimum_required(VERSION 3.14)
project(lab_5_2 C)

set(CMAKE_C_STANDARD 90)

add_executable(lab_5_2 main.c "binary search tree/tree.c" "binary search tree/tree.h" stack/stack.c stack/stack.h "linked list/list.c" "linked list/list.h" defines.h)