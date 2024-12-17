#include "aoc16.h"

char* input = "###############\n"
              "#.......#....E#\n"
              "#.#.###.#.###.#\n"
              "#.....#.#...#.#\n"
              "#.###.#####.#.#\n"
              "#.#.#.......#.#\n"
              "#.#.#####.###.#\n"
              "#...........#.#\n"
              "###.#.#####.#.#\n"
              "#...#.....#.#.#\n"
              "#.#.#.###.#.#.#\n"
              "#.....#...#.#.#\n"
              "#.###.#.#.#.#.#\n"
              "#S..#.....#...#\n"
              "###############";

void get_best_path_score_test() {
    gint64 best_path_score = get_best_path_score(input);
    g_assert_cmpint(best_path_score, ==, 7036);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_best_path_score/test", get_best_path_score_test);
    return g_test_run();
}