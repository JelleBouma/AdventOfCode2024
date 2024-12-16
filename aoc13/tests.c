#include "aoc13.h"

char* input = "Button A: X+94, Y+34\n"
              "Button B: X+22, Y+67\n"
              "Prize: X=8400, Y=5400\n"
              "\n"
              "Button A: X+26, Y+66\n"
              "Button B: X+67, Y+21\n"
              "Prize: X=12748, Y=12176\n"
              "\n"
              "Button A: X+17, Y+86\n"
              "Button B: X+84, Y+37\n"
              "Prize: X=7870, Y=6450\n"
              "\n"
              "Button A: X+69, Y+23\n"
              "Button B: X+27, Y+71\n"
              "Prize: X=18641, Y=10279";

void get_tokens_needed_to_win_all_possible_test() {
    gint64 tokens_needed = get_tokens_needed_to_win_all_possible(input, 0);
    g_assert_cmpint(tokens_needed, ==, 480);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_tokens_needed_to_win_all_possible/test", get_tokens_needed_to_win_all_possible_test);
    return g_test_run();
}