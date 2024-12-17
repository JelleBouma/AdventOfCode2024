#include <stdlib.h>
#include <stdio.h>
#include "aoc16.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc16input.txt", &file_contents, NULL, NULL);
    gint64 best_path_score = get_best_path_score(file_contents);
    printf("best path score: %lld\n", best_path_score);
    return EXIT_SUCCESS;
}