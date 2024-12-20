#include <stdlib.h>
#include <stdio.h>
#include "aoc18.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc18input.txt", &file_contents, NULL, NULL);
    one_time_setup(71, 71);
    gint64 minimum_steps_to_exit = get_minimum_steps_to_exit(file_contents, 1024);
    char* first_blocking_byte = get_first_blocking_byte(file_contents);
    printf("minimum steps to exit: %lld\n", minimum_steps_to_exit);
    printf("first blocking byte: %s\n", first_blocking_byte);
    return EXIT_SUCCESS;
}