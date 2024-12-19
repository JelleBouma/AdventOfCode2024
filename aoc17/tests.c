#include "aoc17.h"

char* input = "Register A: 729\n"
              "Register B: 0\n"
              "Register C: 0\n"
              "\n"
              "Program: 0,1,5,4,3,0";

char* incorrect_register_input = "Register A: 2024\n"
                                 "Register B: 0\n"
                                 "Register C: 0\n"
                                 "\n"
                                 "Program: 0,3,5,4,3,0";

void get_program_output_test() {
    GString* program_output = get_program_output(input);
    g_assert_cmpstr(program_output->str, ==, "4,6,3,5,6,3,5,2,1,0");
}

void get_corrected_register_a_test() {
    gint64 corrected_register_a = get_corrected_register_a(incorrect_register_input);
    g_assert_cmpint(corrected_register_a, ==, 117440);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_program_output/test", get_program_output_test);
    g_test_add_func("/get_corrected_register_a/test", get_corrected_register_a_test);
    return g_test_run();
}