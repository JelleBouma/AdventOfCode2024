#include <stdlib.h>
#include <stdio.h>
#include "aoc19.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc19input.txt", &file_contents, NULL, NULL);
    gint64 possible_design_count = get_possible_design_count(file_contents);
    printf("possible designs: %lld\n", possible_design_count);
    return EXIT_SUCCESS;
}