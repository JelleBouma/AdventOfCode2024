#include <stdlib.h>
#include <stdio.h>
#include "aoc22.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc22input.txt", &file_contents, NULL, NULL);
    gint64 sum_of_secret_numbers = get_sum_of_secret_numbers(file_contents, 2000);
    printf("sum of secret numbers after a day: %lld\n", sum_of_secret_numbers);
    return EXIT_SUCCESS;
}