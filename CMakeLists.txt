cmake_minimum_required(VERSION 3.26)
project(data_structures1 C)

set(CMAKE_C_STANDARD 11)

include_directories(vector)

add_executable(data_structures1
        vector/vector.c
        vector/vector.h
        matrix/matrix.h
        matrix/matrix.c
        lab15.c)
