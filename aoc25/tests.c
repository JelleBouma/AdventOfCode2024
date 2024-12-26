#include "aoc25.h"

char* input = "#####\n"
              ".####\n"
              ".####\n"
              ".####\n"
              ".#.#.\n"
              ".#...\n"
              ".....\n"
              "\n"
              "#####\n"
              "##.##\n"
              ".#.##\n"
              "...##\n"
              "...#.\n"
              "...#.\n"
              ".....\n"
              "\n"
              ".....\n"
              "#....\n"
              "#....\n"
              "#...#\n"
              "#.#.#\n"
              "#.###\n"
              "#####\n"
              "\n"
              ".....\n"
              ".....\n"
              "#.#..\n"
              "###..\n"
              "###.#\n"
              "###.#\n"
              "#####\n"
              "\n"
              ".....\n"
              ".....\n"
              ".....\n"
              "#....\n"
              "#.#..\n"
              "#.#.#\n"
              "#####";

void get_fitting_key_lock_pairs_test() {
    setup(input);
    gint64 fitting_key_lock_pairs = get_fitting_key_lock_pairs();
    g_assert_cmpint(fitting_key_lock_pairs, ==, 3);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_fitting_key_lock_pairs/test", get_fitting_key_lock_pairs_test);
    return g_test_run();
}