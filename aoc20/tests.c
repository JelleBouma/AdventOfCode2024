#include "aoc20.h"

char* input = "###############\n"
              "#...#...#.....#\n"
              "#.#.#.#.#.###.#\n"
              "#S#...#.#.#...#\n"
              "#######.#.#.###\n"
              "#######.#.#...#\n"
              "#######.#.###.#\n"
              "###..E#...#...#\n"
              "###.#######.###\n"
              "#...###...#...#\n"
              "#.#####.#.###.#\n"
              "#.#...#.#.#...#\n"
              "#.#.#.#.#.#.###\n"
              "#...#...#...###\n"
              "###############";

void get_count_of_cheats_that_save_20_test() {
    gint64 cheat_count = get_count_of_cheats_that_save_x(input, 20);
    g_assert_cmpint(cheat_count, ==, 5);
}

void get_count_of_cheats_that_save_12_test() {
    gint64 cheat_count = get_count_of_cheats_that_save_x(input, 12);
    g_assert_cmpint(cheat_count, ==, 8);
}

void get_count_of_cheats_that_save_10_test() {
    gint64 cheat_count = get_count_of_cheats_that_save_x(input, 10);
    g_assert_cmpint(cheat_count, ==, 10);
}

void get_count_of_cheats_that_save_2_test() {
    gint64 cheat_count = get_count_of_cheats_that_save_x(input, 2);
    g_assert_cmpint(cheat_count, ==, 44);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_count_of_cheats_that_save_x/20", get_count_of_cheats_that_save_20_test);
    g_test_add_func("/get_count_of_cheats_that_save_x/12", get_count_of_cheats_that_save_12_test);
    g_test_add_func("/get_count_of_cheats_that_save_x/10", get_count_of_cheats_that_save_10_test);
    g_test_add_func("/get_count_of_cheats_that_save_x/2", get_count_of_cheats_that_save_2_test);
    return g_test_run();
}