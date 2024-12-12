#include "aoc11.h"

char* input = "125 17";

void get_total_stones_6blinks_test() {
    __int128 total_stones = get_total_stones(input, 6);
    g_assert_cmpint(total_stones, ==, 22);
}

void get_total_stones_25blinks_test() {
    __int128 total_stones = get_total_stones(input, 25);
    g_assert_cmpint(total_stones, ==, 55312);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_total_stones/6blinks", get_total_stones_6blinks_test);
    g_test_add_func("/get_total_stones/25blinks", get_total_stones_25blinks_test);
    return g_test_run();
}