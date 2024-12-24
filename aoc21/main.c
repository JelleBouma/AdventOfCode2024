#include <stdlib.h>
#include <stdio.h>
#include "aoc21.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc21input.txt", &file_contents, NULL, NULL);
    gint64 sum_of_complexities = get_sum_of_complexities(file_contents, 2);
    printf("sum of complexities: %lld\n", sum_of_complexities);
    return EXIT_SUCCESS;
}