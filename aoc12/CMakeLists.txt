cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc12 main.c aoc12.c
        aoc12.h
        main.c
        ../shared/pos.c
        ../shared/matrix.c
        ../shared/aocmath.c)
add_executable(aoc12tests tests.c aoc12.c
        ../shared/pos.c
        ../shared/matrix.c
        ../shared/aocmath.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc12 PkgConfig::deps)
target_link_libraries(aoc12tests PkgConfig::deps)