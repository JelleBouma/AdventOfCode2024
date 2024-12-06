#include <stdlib.h>
#include <stdio.h>
#include "aoc5.h"
#include <glib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc5 [file]");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    get_middle_page_total_from_file(file);
    return EXIT_SUCCESS;
}