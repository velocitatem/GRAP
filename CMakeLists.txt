cmake_minimum_required(VERSION 3.16)
project(programming_language_in_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(GRAP
        main.c
        tokens.h
        lexer.c
        lexer.h
        parser.c
        graph.c
        graph.h
        parser.h
        interpreter.c
        interpreter.h
        cli.c
        cli.h
)

target_link_libraries(GRAP m)