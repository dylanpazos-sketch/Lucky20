cmake_minimum_required(VERSION 4.1)
project(Proyecto_final C)

set(CMAKE_C_STANDARD 23)

add_library(Proyecto_final STATIC library.c
        Lucky20.c)
