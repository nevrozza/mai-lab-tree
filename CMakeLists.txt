cmake_minimum_required(VERSION 4.1)
project(tree C)

set(CMAKE_C_STANDARD 17)

add_executable(tree main.c
        tree/tree.c
        tree/tree.h
        cli/cli.c
        cli/cli.h
        utils/utils.c
        utils/utils.h
        stack/stack.c
        stack/stack.h
        tree/tree_utils.c
        tree/tree_utils.h
)
