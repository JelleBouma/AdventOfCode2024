#ifndef ADVENTOFCODE2024_AOC5_H
#define ADVENTOFCODE2024_AOC5_H

#include <stdio.h>

#define page_base 10
#define max_pages 100

struct ordered_page {
    long page;
    int related_to_previous;
};

void get_middle_page_total_from_file(FILE* file);
char* order_page_numbers(char* str, struct ordered_page* pages);
long get_middle_page_total(char* updates, const struct ordered_page* pages);

#endif //ADVENTOFCODE2024_AOC5_H