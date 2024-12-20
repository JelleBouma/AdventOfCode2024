#include "aoc19.h"

char* input = "r, wr, b, g, bwu, rb, gb, br\n"
              "\n"
              "brwrr\n"
              "bggr\n"
              "gbbr\n"
              "rrbgbr\n"
              "ubwu\n"
              "bwurrg\n"
              "brgr\n"
              "bbrgwb";

void get_possible_design_count_test() {
    gint64 possible_design_count = get_possible_design_count(input);
    g_assert_cmpint(possible_design_count, ==, 6);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_possible_design_count/test", get_possible_design_count_test);
    return g_test_run();
}