#ifndef ADVENTOFCODE2024_AOC_STRING_H
#define ADVENTOFCODE2024_AOC_STRING_H

#include "aoc_shared_imports.h"

char** try_split(char* str, char** separators_to_try);
char** split_lines(char* str);
char** split_on_empty_lines(char* str);

#endif //ADVENTOFCODE2024_AOC_STRING_H