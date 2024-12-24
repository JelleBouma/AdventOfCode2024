#include "aoc21.h"

char* input = "029A\n"
              "980A\n"
              "179A\n"
              "456A\n"
              "379A";

void get_sum_of_complexities_test() {
    gint64 sum_of_complexities = get_sum_of_complexities(input, 2);
    g_assert_cmpint(sum_of_complexities, ==, 126384);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_sum_of_complexities/test", get_sum_of_complexities_test);
    return g_test_run();
}