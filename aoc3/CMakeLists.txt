cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc3 main.c aoc3.c
        aoc3.h
        main.c)
add_executable(aoc3tests tests.c aoc3.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc3 PkgConfig::deps)
target_link_libraries(aoc3tests PkgConfig::deps)