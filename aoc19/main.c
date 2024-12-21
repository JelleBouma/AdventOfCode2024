#include <stdlib.h>
#include <stdio.h>
#include "aoc19.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc19input.txt", &file_contents, NULL, NULL);
    one_time_setup(file_contents);
    gint64 possible_design_count = get_possible_design_count();
    gint64 possible_option_count = get_possible_option_count();
    printf("possible designs: %lld\n", possible_design_count);
    printf("possible options: %lld\n", possible_option_count);
    return EXIT_SUCCESS;
}