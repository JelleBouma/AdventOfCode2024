#include <stdlib.h>
#include <stdio.h>
#include "aoc13.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc13 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    gint64 tokens_needed_to_win_all = get_tokens_needed_to_win_all_possible(file_contents, 0);
    gint64 tokens_needed_to_win_all_error_corrected = get_tokens_needed_to_win_all_possible(file_contents, 10000000000000);
    printf("tokens needed to win at all possible claw machines: %lld\n", tokens_needed_to_win_all);
    printf("tokens needed to win at all possible claw machines with error corrected: %lld\n", tokens_needed_to_win_all_error_corrected);
    return EXIT_SUCCESS;
}