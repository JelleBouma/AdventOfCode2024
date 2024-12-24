#include <stdlib.h>
#include <stdio.h>
#include "aoc22.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc22input.txt", &file_contents, NULL, NULL);
    gint64 sum_of_secret_numbers = get_sum_of_secret_numbers(file_contents);
    gint64 highest_total_price = get_highest_total_price(file_contents);
    printf("sum of secret numbers after a day: %lld\n", sum_of_secret_numbers);
    printf("highest total price: %lld\n", highest_total_price);
    return EXIT_SUCCESS;
}