#ifndef ADVENTOFCODE2024_AOC_STRING_H
#define ADVENTOFCODE2024_AOC_STRING_H

#include "aoc_shared_imports.h"

char** split(char* str, char* separator);
char** try_split(char* str, char** separators_to_try);
char** split_lines(char* str);
char** split_on_empty_lines(char* str);
bool starts_with(char* str, char* prefix);
gint32 cmp_alphabetically(gconstpointer a, gconstpointer b);

#endif //ADVENTOFCODE2024_AOC_STRING_H