#include "aoc2.h"

void should_be_safe(char* str, bool use_problem_dampener) {
    g_assert(is_safe(int_list_parse(str), use_problem_dampener));
}

void should_be_unsafe(char* str, bool use_problem_dampener) {
    g_assert(!is_safe(int_list_parse(str), use_problem_dampener));
}

void ascending_should_be_safe_test() {
    should_be_safe("1 2 3 4 5", false);
}

void descending_should_be_safe_test() {
    should_be_safe("5 4 3 2", false);
}

void descending_one_ascending_dampened_should_be_safe_test() {
    should_be_safe("5 6 3 2", true);
}

void descending_two_ascending_dampened_should_be_unsafe_test() {
    should_be_unsafe("5 6 7 3 2", true);
}

void one_dupe_number_should_be_unsafe_test() {
    should_be_unsafe("6 6 5", false);
}

void one_dupe_number_dampened_should_be_safe_test() {
    should_be_safe("6 6 5", true);
}

void two_dupe_numbers_dampened_should_be_unsafe_test() {
    should_be_unsafe("6 6 6 5", true);
}

void bad_difference_should_be_unsafe_test()
{
    should_be_unsafe("6 10 11", false);
}

void bad_difference_dampened_should_be_safe_test()
{
    should_be_safe("6 10 11", true);
}

void two_bad_differences_dampened_should_be_unsafe_test()
{
    should_be_unsafe("9 7 2 1", true);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/is_safe/ascending_should_be_safe", ascending_should_be_safe_test);
    g_test_add_func("/is_safe/descending_should_be_safe", descending_should_be_safe_test);
    g_test_add_func("/is_safe/descending_one_ascending_dampened_should_be_safe", descending_one_ascending_dampened_should_be_safe_test);
    g_test_add_func("/is_safe/descending_two_ascending_dampened_should_be_unsafe", descending_two_ascending_dampened_should_be_unsafe_test);
    g_test_add_func("/is_safe/one_dupe_number_should_be_unsafe", one_dupe_number_should_be_unsafe_test);
    g_test_add_func("/is_safe/one_dupe_number_dampened_should_be_safe", one_dupe_number_dampened_should_be_safe_test);
    g_test_add_func("/is_safe/two_dupe_numbers_dampened_should_be_unsafe", two_dupe_numbers_dampened_should_be_unsafe_test);
    g_test_add_func("/is_safe/bad_difference_should_be_unsafe", bad_difference_should_be_unsafe_test);
    g_test_add_func("/is_safe/bad_difference_dampened_should_be_safe", bad_difference_dampened_should_be_safe_test);
    g_test_add_func("/is_safe/two_bad_differences_dampened_should_be_unsafe", two_bad_differences_dampened_should_be_unsafe_test);
    return g_test_run();
}