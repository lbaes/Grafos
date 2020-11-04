cmake_minimum_required(VERSION 3.10)

# Projeto
project(LinkedList VERSION 1.0)

add_library(LinkedList linked_list.c linked_list.h)

target_include_directories(LinkedList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Padrao c11
set(CMAKE_C_STANDARD C11)








