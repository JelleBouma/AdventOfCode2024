cmake_minimum_required(VERSION 3.20)
project(aoc2 C)

set(CMAKE_C_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_executable(aoc8 main.c aoc8.c
        aoc8.h
        main.c
        ../shared/pos.c
        ../shared/matrix.c)
add_executable(aoc8tests tests.c aoc8.c
        ../shared/pos.c
        ../shared/matrix.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(aoc8 PkgConfig::deps)
target_link_libraries(aoc8tests PkgConfig::deps)