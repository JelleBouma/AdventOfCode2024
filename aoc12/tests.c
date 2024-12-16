#include "aoc12.h"

char* input = "RRRRIICCFF\n"
              "RRRRIICCCF\n"
              "VVRRRCCFFF\n"
              "VVRCCCJFFF\n"
              "VVVVCJJCFE\n"
              "VVIVCCJJEE\n"
              "VVIIICJJEE\n"
              "MIIIIIJJEE\n"
              "MIIISIJEEE\n"
              "MMMISSJEEE";

void get_total_fence_price_no_discount_test() {
    gint64 total_fence_price = get_total_fence_price(input, false);
    g_assert_cmpint(total_fence_price, ==, 1930);
}

char* input_bulk_discount_368 = "AAAAAA\n"
                                "AAABBA\n"
                                "AAABBA\n"
                                "ABBAAA\n"
                                "ABBAAA\n"
                                "AAAAAA";

void get_total_fence_price_with_bulk_discount_368_test() {
    gint64 total_fence_price = get_total_fence_price(input_bulk_discount_368, true);
    g_assert_cmpint(total_fence_price, ==, 368);
}

void get_total_fence_price_with_bulk_discount_test() {
    gint64 total_fence_price = get_total_fence_price(input, true);
    g_assert_cmpint(total_fence_price, ==, 1206);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_total_fence_price/no_discount", get_total_fence_price_no_discount_test);
    g_test_add_func("/get_total_fence_price/bulk_discount_368", get_total_fence_price_with_bulk_discount_368_test);
    g_test_add_func("/get_total_fence_price/bulk_discount", get_total_fence_price_with_bulk_discount_test);
    return g_test_run();
}