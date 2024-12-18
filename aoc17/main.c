#include <stdlib.h>
#include <stdio.h>
#include "aoc17.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc17input.txt", &file_contents, NULL, NULL);
    GString* program_output = get_program_output(file_contents);
    printf("program output: %s\n", program_output->str);
    return EXIT_SUCCESS;
}