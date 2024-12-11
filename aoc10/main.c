#include <stdlib.h>
#include <stdio.h>
#include "aoc10.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc10 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long long total_trailhead_score = get_total_trailhead_score(file_contents);
    long long total_trailhead_rating = get_total_trailhead_rating(file_contents);
    printf("total trailhead score: %lld\n", total_trailhead_score);
    printf("total trailhead rating: %lld\n", total_trailhead_rating);
    return EXIT_SUCCESS;
}