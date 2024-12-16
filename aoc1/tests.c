#include "aoc1.h"

char* input = "3   4\n"
              "4   3\n"
              "2   5\n"
              "1   3\n"
              "3   9\n"
              "3   3";


void get_total_distance_test() {
    gint64 total_distance = get_total_distance(input);
    g_assert_cmpint(total_distance, ==, 11);
}

void get_similarity_score_test() {
    gint64 similarity_score = get_similarity_score(input);
    g_assert_cmpint(similarity_score, ==, 31);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_total_distance/test", get_total_distance_test);
    g_test_add_func("/get_similarity_score/test", get_similarity_score_test);
    return g_test_run();
}