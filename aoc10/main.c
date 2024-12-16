#include <stdlib.h>
#include <stdio.h>
#include "aoc10.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc10input.txt", &file_contents, NULL, NULL);
    gint64 total_trailhead_score = get_total_trailhead_score(file_contents);
    gint64 total_trailhead_rating = get_total_trailhead_rating(file_contents);
    printf("total trailhead score: %lld\n", total_trailhead_score);
    printf("total trailhead rating: %lld\n", total_trailhead_rating);
    return EXIT_SUCCESS;
}