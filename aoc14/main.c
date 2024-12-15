#include <stdlib.h>
#include <stdio.h>
#include "aoc14.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc14 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    gint64 safety_factor = get_safety_factor(file_contents, 101, 103, 100);
    gint64 seconds_to_tree = get_seconds_to_lowest_safety_factor(file_contents, 101, 103);
    printf("safety factor: %lld\n", safety_factor);
    printf("seconds to tree easter egg: %lld\n", seconds_to_tree);
    return EXIT_SUCCESS;
}