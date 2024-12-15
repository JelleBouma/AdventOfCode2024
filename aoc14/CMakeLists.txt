cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc14 main.c aoc14.c
        aoc14.h
        main.c
        ../shared/pos.c
        ../shared/int_list.c
        ../shared/int_list.c)
add_executable(aoc14tests tests.c aoc14.c
        ../shared/pos.c
        ../shared/int_list.c
        ../shared/int_list.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc14 PkgConfig::deps)
target_link_libraries(aoc14tests PkgConfig::deps)