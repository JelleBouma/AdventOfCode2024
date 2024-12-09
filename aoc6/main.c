#include <stdlib.h>
#include <stdio.h>
#include "aoc6.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc6 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long distinct_positions = count_distinct_positions_in_path(file_contents);
    long infinitely_blockable_positions_in_path = count_infinitely_blockable_positions_in_path(file_contents);
    printf("distinct positions visited by guard: %ld\n", distinct_positions);
    printf("infinitely blockable positions in path: %ld\n", infinitely_blockable_positions_in_path);
    return EXIT_SUCCESS;
}