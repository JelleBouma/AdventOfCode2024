#include "aoc22.h"

char* input = "1\n"
              "10\n"
              "100\n"
              "2024";

void get_sum_of_secret_numbers_test() {
    gint64 sum_of_secret_numbers = get_sum_of_secret_numbers(input, 2000);
    g_assert_cmpint(sum_of_secret_numbers, ==, 37327623);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_sum_of_secret_numbers/test", get_sum_of_secret_numbers_test);
    return g_test_run();
}