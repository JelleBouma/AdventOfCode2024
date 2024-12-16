#ifndef AOC5_H
#define AOC5_H

#include <aoc_shared.h>

typedef struct MiddlePageSums
{
    gint64 correct_ordering_middle_page_sum;
    gint64 reordered_middle_page_sum;
} MiddlePageSums;

MiddlePageSums get_middle_page_total(char* str);
GHashTable* build_rule_table(char* str);
MiddlePageSums get_middle_page_sums(char* updates, GHashTable* rule_table);

#endif //AOC5_H