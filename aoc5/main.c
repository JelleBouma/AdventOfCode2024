#include <stdlib.h>
#include <stdio.h>
#include "aoc5.h"

int main(int argc, char **argv) {
    char* file_contents;
    g_file_get_contents("aoc5input.txt", &file_contents, NULL, NULL);
    MiddlePageSums sums = get_middle_page_total(file_contents);
    printf("Correctly ordered middle page total: %ld\n", sums.correct_ordering_middle_page_sum);
    printf("Reordered middle page total: %ld\n", sums.reordered_middle_page_sum);
    return EXIT_SUCCESS;
}