#include "aoc18.h"

char* input = "5,4\n"
              "4,2\n"
              "4,5\n"
              "3,0\n"
              "2,1\n"
              "6,3\n"
              "2,4\n"
              "1,5\n"
              "0,6\n"
              "3,3\n"
              "2,6\n"
              "5,1\n"
              "1,2\n"
              "5,5\n"
              "2,5\n"
              "6,5\n"
              "1,4\n"
              "0,4\n"
              "6,4\n"
              "1,1\n"
              "6,1\n"
              "1,0\n"
              "0,5\n"
              "1,6\n"
              "2,0";

void get_minimum_steps_to_exit_test() {
    one_time_setup(7, 7);
    gint64 minimum_steps = get_minimum_steps_to_exit(input, 12);
    g_assert_cmpint(minimum_steps, ==, 22);
}

void get_first_blocking_byte_test() {
    one_time_setup(7, 7);
    char* first_blocking_byte = get_first_blocking_byte(input);
    g_assert_cmpstr(first_blocking_byte, ==, "6,1");
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_minimum_steps_to_exit/test", get_minimum_steps_to_exit_test);
    g_test_add_func("/get_first_blocking_byte/test", get_first_blocking_byte_test);
    return g_test_run();
}