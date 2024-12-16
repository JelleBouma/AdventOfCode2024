#include <stdlib.h>
#include <stdio.h>
#include "aoc3.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc3input.txt", &file_contents, NULL, NULL);
    gint64 sum = get_sum_of_muls(file_contents);
    gint64 sum_with_dos_and_donts = get_sum_of_muls_with_dos_and_donts(file_contents);
    printf("sum of multiplications: %ld\n", sum);
    printf("sum of multiplications with do's and don'ts: %ld\n", sum_with_dos_and_donts);
    return EXIT_SUCCESS;
}