#include <stdlib.h>
#include <stdio.h>
#include "aoc20.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc20input.txt", &file_contents, NULL, NULL);
    setup(file_contents);
    gint64 count_of_2ps_cheats_that_save_100ps = get_count_of_cheats_that_save_x(2, 100);
    gint64 count_of_20ps_cheats_that_save_100ps = get_count_of_cheats_that_save_x(20, 100);
    printf("count of 2 picosecond cheats that save 100 picoseconds: %lld\n", count_of_2ps_cheats_that_save_100ps);
    printf("count of 20 picosecond cheats that save 100 picoseconds: %lld\n", count_of_20ps_cheats_that_save_100ps);
    return EXIT_SUCCESS;
}