#include "aoc22.h"

char* sum_of_secret_numbers_input = "1\n"
                                    "10\n"
                                    "100\n"
                                    "2024";

void get_sum_of_secret_numbers_test() {
    gint64 sum_of_secret_numbers = get_sum_of_secret_numbers(sum_of_secret_numbers_input);
    g_assert_cmpint(sum_of_secret_numbers, ==, 37327623);
}

char* highest_total_price_input = "1\n"
                                  "2\n"
                                  "3\n"
                                  "2024";

void get_highest_total_price_test() {
    gint64 highest_total_price = get_highest_total_price(highest_total_price_input);
    g_assert_cmpint(highest_total_price, ==, 23);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_sum_of_secret_numbers/test", get_sum_of_secret_numbers_test);
    g_test_add_func("/get_highest_total_price/test", get_highest_total_price_test);
    return g_test_run();
}