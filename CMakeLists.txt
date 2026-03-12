cmake_minimum_required(VERSION 4.1)
project(tree C)

set(CMAKE_C_STANDARD 17)

add_executable(tree main.c
        tree/tree.c
        tree/tree.h
        cli/cli.c
        cli/cli.h)
