#include "aoc6.h"

char* input = "....#.....\n"
              ".........#\n"
              "..........\n"
              "..#.......\n"
              ".......#..\n"
              "..........\n"
              ".#..^.....\n"
              "........#.\n"
              "#.........\n"
              "......#...";

void count_distinct_positions_in_path_test() {
    long count = count_distinct_positions_in_path(input);
    g_assert_cmpint(count, ==, 41);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/count_distinct_positions_in_path/test", count_distinct_positions_in_path_test);
    return g_test_run();
}