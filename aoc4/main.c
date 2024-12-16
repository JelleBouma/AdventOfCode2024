#include <stdlib.h>
#include <stdio.h>
#include "aoc4.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc4input.txt", &file_contents, NULL, NULL);
    gint64 needle_count = full_word_search_2d("XMAS", file_contents);
    gint64 cross_mas_count = cross_mas_search_2d(file_contents);
    printf("XMAS count: %lld\n", needle_count);
    printf("X-MAS count: %lld\n", cross_mas_count);
    return EXIT_SUCCESS;
}