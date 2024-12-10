#include <stdlib.h>
#include <stdio.h>
#include "aoc8.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc8 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long antinode_location_count = get_antinode_location_count(file_contents, false);
    long resonant_antinode_location_count = get_antinode_location_count(file_contents, true);
    printf("antinode location count: %ld\n", antinode_location_count);
    printf("resonant antinode location count: %ld\n", resonant_antinode_location_count);
    return EXIT_SUCCESS;
}