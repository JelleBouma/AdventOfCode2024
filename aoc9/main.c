#include <stdlib.h>
#include <stdio.h>
#include "aoc9.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc9 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    gint64 by_block_checksum = get_checksum(file_contents, last_block_to_first_empty_slot);
    gint64 by_file_checksum = get_checksum(file_contents, last_file_to_first_empty_slot);
    printf("checksum after moving blocks: %lld\n", by_block_checksum);
    printf("checksum after moving files: %lld\n", by_file_checksum);
    return EXIT_SUCCESS;
}