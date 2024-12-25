#include "aoc24.h"

char* input = "x00: 1\n"
              "x01: 1\n"
              "x02: 1\n"
              "y00: 0\n"
              "y01: 1\n"
              "y02: 0\n"
              "\n"
              "x00 AND y00 -> z00\n"
              "x01 XOR y01 -> z01\n"
              "x02 OR y02 -> z02";

void get_output_test() {
    gint64 output = get_output(input);
    g_assert_cmpint(output, ==, 4);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_output/test", get_output_test);
    return g_test_run();
}