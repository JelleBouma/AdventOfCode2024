#include <stdlib.h>
#include <stdio.h>
#include "aoc7.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc7 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    long long plus_mul_res = get_total_calibration_result(file_contents, plus_mul, 2);
    long long plus_mul_concat_res = get_total_calibration_result(file_contents, plus_mul_concat, 3);
    printf("total calibration result (+, *): %lld\n", plus_mul_res);
    printf("total calibration result (+, *, ||): %lld\n", plus_mul_concat_res);
    return EXIT_SUCCESS;
}