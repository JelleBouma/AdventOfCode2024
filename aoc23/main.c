#include <stdlib.h>
#include <stdio.h>
#include "aoc23.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc23input.txt", &file_contents, NULL, NULL);
    setup(file_contents);
    gint64 size_3_groups_with_t_computer = count_t_triangles();
    char* pwd = get_lan_party_password();
    printf("size 3 groups with possible Chief Historian: %lld\n", size_3_groups_with_t_computer);
    printf("lan party password: %s\n", pwd);
    return EXIT_SUCCESS;
}