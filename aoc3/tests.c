#include "aoc3.h"

void get_sum_of_muls_test() {
    char* input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
    gint64 output = get_sum_of_muls(input);
    g_assert_cmpint(output, ==, 161);
}

void get_sum_of_muls_with_dos_and_donts_test() {
    char* input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    gint64 output = get_sum_of_muls_with_dos_and_donts(input);
    g_assert_cmpint(output, ==, 48);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_sum_of_muls", get_sum_of_muls_test);
    g_test_add_func("/get_sum_of_muls_with_dos_and_donts", get_sum_of_muls_with_dos_and_donts_test);
    return g_test_run();
}