cmake_minimum_required(VERSION 3.20)
project(AdventOfCode2024 C)
set(CMAKE_C_STANDARD 11)

add_library(AocShared STATIC
        aoc_shared.h
        aoc_int_list.c
        aoc_math.c
        aoc_pos.c
        aoc_matrix.c
        aoc_string.c
        aoc_pos_dict.c
        aoc_pos_dict.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(AocShared PkgConfig::deps)