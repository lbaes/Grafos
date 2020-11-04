cmake_minimum_required(VERSION 3.10)

# Projeto
project(Kruskal VERSION 1.0)

# Libs
add_subdirectory(libs)

# Files
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

# Executavel
add_executable(Kruskal src/main.c ${headers})

# includes
target_include_directories(Kruskal PUBLIC
                          "${PROJECT_SOURCE_DIR}/libs/"
                          "${PROJECT_SOURCE_DIR}/libs/LinkedList/"
                          "${PROJECT_SOURCE_DIR}/libs/GrafoADJ/")

target_link_libraries(Kruskal PUBLIC LinkedList GrafoADJ GrafoMAT)

# Padrao c11
set(CMAKE_C_STANDARD C11)