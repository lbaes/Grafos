cmake_minimum_required(VERSION 3.10)

# Projeto
project(GrafoADJ VERSION 1.0)

# executavel
add_library(GrafoADJ grafo_adj.c grafo_adj.h ../LinkedList/linked_list.h)

# padrao c11
set(CMAKE_C_STANDARD C11)

target_include_directories(GrafoADJ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../LinkedList/)

target_link_libraries(GrafoADJ LinkedList)





