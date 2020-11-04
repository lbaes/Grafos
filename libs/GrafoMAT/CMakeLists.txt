cmake_minimum_required(VERSION 3.10)

# Projeto
project(GrafoMAT VERSION 1.0)

# executavel
add_library(GrafoMAT grafo_mat.c grafo_mat.h)

# padrao c11
set(CMAKE_C_STANDARD C11)

target_include_directories(GrafoMAT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)





