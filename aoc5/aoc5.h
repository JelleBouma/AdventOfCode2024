#ifndef ADVENTOFCODE2024_AOC5_H
#define ADVENTOFCODE2024_AOC5_H

#include <stdio.h>
#include <glib.h>

#define page_base 10

typedef struct MiddlePageSums
{
    long correct_ordering_middle_page_sum;
    long reordered_middle_page_sum;
} MiddlePageSums;

void get_middle_page_total_from_file(FILE* file);
GHashTable* build_rule_table(char** str);
MiddlePageSums get_middle_page_sums(char* updates, GHashTable* rule_table);

#endif //ADVENTOFCODE2024_AOC5_H