cmake_minimum_required(VERSION 3.20)
project(AdventOfCode2024 C)
include(CTest)
set(CMAKE_C_STANDARD 11)

add_subdirectory(shared)
foreach(day RANGE 1 25)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/aoc${day}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/aoc${day}input.txt COPYONLY)
    add_executable(aoc${day} aoc${day}/main.c aoc${day}/aoc${day}.c)
    add_executable(aoc${day}tests aoc${day}/tests.c aoc${day}/aoc${day}.c)
    add_test(NAME aoc${day}tests COMMAND aoc${day}tests)
    target_link_libraries(aoc${day} PUBLIC AocShared)
    target_link_libraries(aoc${day}tests PUBLIC AocShared)
    target_include_directories(aoc${day} PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/shared")
    target_include_directories(aoc${day}tests PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/shared")
endforeach()