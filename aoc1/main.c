#include <stdio.h>
#include "aoc1.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc1input.txt", &file_contents, NULL, NULL);
    gint64 total_distance = get_total_distance(file_contents);
    gint64 similarity_score = get_similarity_score(file_contents);
    printf("Total distance: %lld\n", total_distance);
    printf("Similarity score: %lld\n", similarity_score);
}