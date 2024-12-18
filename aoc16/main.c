#include <stdlib.h>
#include <stdio.h>
#include "aoc16.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc16input.txt", &file_contents, NULL, NULL);
    init_path_traverse(file_contents);
    gint64 best_path_score = get_best_path_score();
    gint32 best_paths_tile_count = get_best_paths_tile_count();
    printf("best path score: %lld\n", best_path_score);
    printf("best paths tile count: %d\n", best_paths_tile_count);
    return EXIT_SUCCESS;
}