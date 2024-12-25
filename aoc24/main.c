#include <stdlib.h>
#include <stdio.h>
#include "aoc24.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc24input.txt", &file_contents, NULL, NULL);
    gint64 output = get_output(file_contents);
    printf("output: %lld\n", output);
    return EXIT_SUCCESS;
}