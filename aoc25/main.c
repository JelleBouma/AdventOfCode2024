#include <stdlib.h>
#include <stdio.h>
#include "aoc25.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc25input.txt", &file_contents, NULL, NULL);
    setup(file_contents);
    gint64 fitting_key_lock_pairs = get_fitting_key_lock_pairs();
    printf("fitting key lock pairs: %lld\n", fitting_key_lock_pairs);
    return EXIT_SUCCESS;
}