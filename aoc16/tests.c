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
    init_path_traverse(input);
    gint64 best_path_score = get_best_path_score();
    g_assert_cmpint(best_path_score, ==, 7036);
}

void get_best_paths_tile_count_test() {
    init_path_traverse(input);
    gint64 best_paths_tile_count = get_best_paths_tile_count();
    g_assert_cmpint(best_paths_tile_count, ==, 45);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_best_path_score/test", get_best_path_score_test);
    g_test_add_func("/get_best_paths_tile_count/test", get_best_paths_tile_count_test);
    return g_test_run();
}