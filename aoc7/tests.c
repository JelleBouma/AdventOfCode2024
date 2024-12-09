#include "aoc7.h"

char* input = "190: 10 19\n"
              "3267: 81 40 27\n"
              "83: 17 5\n"
              "156: 15 6\n"
              "7290: 6 8 6 15\n"
              "161011: 16 10 13\n"
              "192: 17 8 14\n"
              "21037: 9 7 18 13\n"
              "292: 11 6 16 20";

void get_total_calibration_result_plus_mul_test() {
    long long total_calibration_result = get_total_calibration_result(input, plus_mul, 2);
    g_assert_cmpint(total_calibration_result, ==, 3749);
}

void get_total_calibration_result_plus_mul_concat_test() {
    long long total_calibration_result = get_total_calibration_result(input, plus_mul_concat, 3);
    g_assert_cmpint(total_calibration_result, ==, 11387);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_total_calibration_result/plus_mul", get_total_calibration_result_plus_mul_test);
    g_test_add_func("/get_total_calibration_result/plus_mul_concat", get_total_calibration_result_plus_mul_concat_test);
    return g_test_run();
}