#include <stdlib.h>
#include <stdio.h>
#include "aoc21.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc21input.txt", &file_contents, NULL, NULL);
    gint64 sum_of_complexities_2_keypads = get_sum_of_complexities(file_contents, 2);
    gint64 sum_of_complexities_25_keypads = get_sum_of_complexities(file_contents, 25);
    printf("sum of complexities (2 keypads): %lld\n", sum_of_complexities_2_keypads);
    printf("sum of complexities (25 keypads): %lld\n", sum_of_complexities_25_keypads);
    return EXIT_SUCCESS;
}