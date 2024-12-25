#include <stdlib.h>
#include <stdio.h>
#include "aoc23.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc23input.txt", &file_contents, NULL, NULL);
    gint64 size_3_groups_with_t_computer = count_t_triangles(file_contents);
    printf("size 3 groups with possible Chief Historian: %lld\n", size_3_groups_with_t_computer);
    return EXIT_SUCCESS;
}