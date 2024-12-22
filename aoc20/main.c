#include <stdlib.h>
#include <stdio.h>
#include "aoc20.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc20input.txt", &file_contents, NULL, NULL);
    gint64 count_of_cheats_that_save_100ps = get_count_of_cheats_that_save_x(file_contents, 100);
    printf("count of cheats that save 100 picoseconds: %lld\n", count_of_cheats_that_save_100ps);
    return EXIT_SUCCESS;
}