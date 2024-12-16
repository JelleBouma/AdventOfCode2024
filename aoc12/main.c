#include <stdlib.h>
#include <stdio.h>
#include "aoc12.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc12 [file]");
        return EXIT_FAILURE;
    }
    char* file_contents;
    g_file_get_contents(argv[1], &file_contents, NULL, NULL);
    gint64 total_fence_price = get_total_fence_price(file_contents, false);
    gint64 total_fence_price_with_bulk_discount = get_total_fence_price(file_contents, true);
    printf("total fence price: %lld\n", total_fence_price);
    printf("total fence price with bulk discount: %lld\n", total_fence_price_with_bulk_discount);
    return EXIT_SUCCESS;
}