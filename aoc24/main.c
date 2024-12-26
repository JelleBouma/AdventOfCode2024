#include <stdlib.h>
#include <stdio.h>
#include "aoc24.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc24input.txt", &file_contents, NULL, NULL);
    setup(file_contents);
    gint64 output = get_output();
    char* crossed_wires = get_crossed_wires();
    printf("output: %lld\n", output);
    printf("crossed wires: %s\n", crossed_wires);
    return EXIT_SUCCESS;
}