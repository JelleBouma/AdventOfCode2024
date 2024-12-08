#include <stdlib.h>
#include <stdio.h>
#include "aoc4.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc4 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long needle_count = full_word_search_2d("XMAS", file_contents);
    long cross_mas_count = cross_mas_search_2d(file_contents);
    printf("XMAS count: %ld\n", needle_count);
    printf("X-MAS count: %ld\n", cross_mas_count);
    return EXIT_SUCCESS;
}