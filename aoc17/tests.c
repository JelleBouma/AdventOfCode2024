#include "aoc17.h"

char* input = "Register A: 729\n"
              "Register B: 0\n"
              "Register C: 0\n"
              "\n"
              "Program: 0,1,5,4,3,0";

void get_program_output_test() {
    GString* program_output = get_program_output(input);
    g_assert_cmpstr(program_output->str, ==, "4,6,3,5,6,3,5,2,1,0");
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_program_output/test", get_program_output_test);
    return g_test_run();
}