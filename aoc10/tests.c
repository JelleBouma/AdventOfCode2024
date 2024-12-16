#include "aoc10.h"

char* input = "89010123\n"
              "78121874\n"
              "87430965\n"
              "96549874\n"
              "45678903\n"
              "32019012\n"
              "01329801\n"
              "10456732";

void get_total_trailhead_score_test() {
    gint64 total_trailhead_score = get_total_trailhead_score(input);
    g_assert_cmpint(total_trailhead_score, ==, 36);
}

void get_total_trailhead_rating_test() {
    gint64 total_trailhead_score = get_total_trailhead_rating(input);
    g_assert_cmpint(total_trailhead_score, ==, 81);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_total_trailhead_score/test", get_total_trailhead_score_test);
    g_test_add_func("/get_total_trailhead_rating/test", get_total_trailhead_rating_test);
    return g_test_run();
}