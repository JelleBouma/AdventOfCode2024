#include "aoc4.h"

char* input = "MMMSXXMASM\n"
              "MSAMXMSMSA\n"
              "AMXSXMAAMM\n"
              "MSAMASMSMX\n"
              "XMASAMXAMM\n"
              "XXAMMXXAMA\n"
              "SMSMSASXSS\n"
              "SAXAMASAAA\n"
              "MAMMMXMMMM\n"
              "MXMXAXMASX";

void directional_word_search_2d_test(Pos(*next_pos_func)(Pos), long expected_count) {
    Matrix haystack = new_matrix(input);
    long count = directional_word_search_2d("XMAS", haystack, next_pos_func);
    g_assert_cmpint(count, ==, expected_count);
}

void directional_word_search_2d_up_test() {
    directional_word_search_2d_test(up, 2);
}

void directional_word_search_2d_right_test() {
    directional_word_search_2d_test(right, 3);
}

void full_word_search_2d_test() {
    long count = full_word_search_2d("XMAS", input);
    g_assert_cmpint(count, ==, 18);
}

void cross_mas_search_2d_test() {
    long count = cross_mas_search_2d(input);
    g_assert_cmpint(count, ==, 9);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/directional_word_search_2d/up", directional_word_search_2d_up_test);
    g_test_add_func("/directional_word_search_2d/right", directional_word_search_2d_right_test);
    g_test_add_func("/full_word_search_2d/test", full_word_search_2d_test);
    g_test_add_func("/cross_mas_search_2d/test", cross_mas_search_2d_test);
    return g_test_run();
}