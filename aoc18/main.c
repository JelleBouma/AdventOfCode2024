#include <stdlib.h>
#include <stdio.h>
#include "aoc18.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc18input.txt", &file_contents, NULL, NULL);
    gint64 minimum_steps_to_exit = get_minimum_steps_to_exit(file_contents, 1024, 71, 71);
    printf("minimum steps to exit: %lld\n", minimum_steps_to_exit);
    return EXIT_SUCCESS;
}