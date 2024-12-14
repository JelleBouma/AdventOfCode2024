cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc13 main.c aoc13.c
        aoc13.h
        main.c
        ../shared/aocmath.c
        ../shared/aocmath.h
        ../shared/int_list.c
        ../shared/int_list.h)
add_executable(aoc13tests tests.c aoc13.c
        ../shared/aocmath.c
        ../shared/aocmath.h
        ../shared/int_list.c
        ../shared/int_list.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc13 PkgConfig::deps)
target_link_libraries(aoc13tests PkgConfig::deps)

add_compile_options(
        $<$<CONFIG:RELEASE>:-O3>
)