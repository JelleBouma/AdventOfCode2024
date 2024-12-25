#include "aoc23.h"

char* input = "kh-tc\n"
              "qp-kh\n"
              "de-cg\n"
              "ka-co\n"
              "yn-aq\n"
              "qp-ub\n"
              "cg-tb\n"
              "vc-aq\n"
              "tb-ka\n"
              "wh-tc\n"
              "yn-cg\n"
              "kh-ub\n"
              "ta-co\n"
              "de-co\n"
              "tc-td\n"
              "tb-wq\n"
              "wh-td\n"
              "ta-ka\n"
              "td-qp\n"
              "aq-cg\n"
              "wq-ub\n"
              "ub-vc\n"
              "de-ta\n"
              "wq-aq\n"
              "wq-vc\n"
              "wh-yn\n"
              "ka-de\n"
              "kh-ta\n"
              "co-tc\n"
              "wh-qp\n"
              "tb-vc\n"
              "td-yn";

void count_t_triangles_test() {
    gint64 t_triangles = count_t_triangles(input);
    g_assert_cmpint(t_triangles, ==, 7);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/count_t_triangles/test", count_t_triangles_test);
    return g_test_run();
}