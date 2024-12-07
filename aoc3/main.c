#include <stdlib.h>
#include <stdio.h>
#include "aoc3.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc3 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long sum = get_sum_of_muls(file_contents);
    long sum_with_dos_and_donts = get_sum_of_muls_with_dos_and_donts(file_contents);
    printf("sum of multiplications: %ld\n", sum);
    printf("sum of multiplications with do's and don'ts: %ld\n", sum_with_dos_and_donts);
    return EXIT_SUCCESS;
}