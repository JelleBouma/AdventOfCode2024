#include <stdlib.h>
#include <stdio.h>
#include "aoc15.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc15input.txt", &file_contents, NULL, NULL);
    gint64 sum_of_box_gps_coordinates = get_sum_of_box_gps_coordinates(file_contents);
    gint64 sum_of_wide_box_gps_coordinates = get_sum_of_box_gps_coordinates_scaled_up(file_contents);
    printf("sum of box GPS coordinates: %lld\n", sum_of_box_gps_coordinates);
    printf("sum of wide box GPS coordinates: %lld\n", sum_of_wide_box_gps_coordinates);
    return EXIT_SUCCESS;
}