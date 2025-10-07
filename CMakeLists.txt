cmake_minimum_required(VERSION 4.0)
project(TPMALLOC C)

set(CMAKE_C_STANDARD 11)

add_executable(TPMALLOC main.c
        main.h
)
