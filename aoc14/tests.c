#include "aoc14.h"

char* input = "p=0,4 v=3,-3\n"
              "p=6,3 v=-1,-3\n"
              "p=10,3 v=-1,2\n"
              "p=2,0 v=2,-1\n"
              "p=0,0 v=1,3\n"
              "p=3,0 v=-2,-2\n"
              "p=7,6 v=-1,-3\n"
              "p=3,0 v=-1,-2\n"
              "p=9,3 v=2,3\n"
              "p=7,3 v=-1,2\n"
              "p=2,4 v=2,-3\n"
              "p=9,5 v=-3,-3";

void get_safety_factor_test() {
    gint64 safety_factor = get_safety_factor(input, 11, 7);
    g_assert_cmpint(safety_factor, ==, 12);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_safety_factor/test", get_safety_factor_test);
    return g_test_run();
}