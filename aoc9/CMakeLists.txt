cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc9 main.c aoc9.c
        aoc9.h
        main.c)
add_executable(aoc9tests tests.c aoc9.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc9 PkgConfig::deps)
target_link_libraries(aoc9tests PkgConfig::deps)