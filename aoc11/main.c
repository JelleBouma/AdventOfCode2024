#include <stdlib.h>
#include <stdio.h>
#include "aoc11.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc11 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    gint64 total_stones_25 = get_total_stones(file_contents, 25);
    gint64 total_stones_75 = get_total_stones(file_contents, 75);
    printf("total stones after 25 blinks: %lld\n", total_stones_25);
    printf("total stones after 75 blinks: %lld\n", total_stones_75);
    return EXIT_SUCCESS;
}