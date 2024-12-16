#include "aoc8.h"

char* input = "............\n"
              "........0...\n"
              ".....0......\n"
              ".......0....\n"
              "....0.......\n"
              "......A.....\n"
              "............\n"
              "............\n"
              "........A...\n"
              ".........A..\n"
              "............\n"
              "............";

void get_antinode_location_count_test() {
    gint64 antinode_location_count = get_antinode_location_count(input, false);
    g_assert_cmpint(antinode_location_count, ==, 14);
}

void get_antinode_location_count_resonant_test() {
    gint64 antinode_location_count = get_antinode_location_count(input, true);
    g_assert_cmpint(antinode_location_count, ==, 34);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_antinode_location_count/not_resonant", get_antinode_location_count_test);
    g_test_add_func("/get_antinode_location_count/resonant", get_antinode_location_count_resonant_test);
    return g_test_run();
}