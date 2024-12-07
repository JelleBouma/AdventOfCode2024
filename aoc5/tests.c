#include <assert.h>
#include "aoc5.h"

 char* input = "2|3\n"
"1|2\n"
"1|5\n"
"5|3\n"
"\n"
"5,3,1\n"
"1,2,3\n"
"1,5,3\n";

void build_rule_table_test() {
    GHashTable* rule_table = build_rule_table(&input);
    g_assert(g_hash_table_contains(rule_table, GINT_TO_POINTER(2)));
    g_assert(g_hash_table_contains(rule_table, GINT_TO_POINTER(1)));
    g_assert(g_hash_table_contains(rule_table, GINT_TO_POINTER(5)));
    g_assert_cmpint(g_hash_table_size(rule_table), ==, 3);
    GHashTable* rules_for_page_1 = g_hash_table_lookup(rule_table, GINT_TO_POINTER(1));
    g_assert_cmpint(g_hash_table_size(rules_for_page_1), ==, 2);
    g_assert(g_hash_table_contains(rules_for_page_1, GINT_TO_POINTER(2)));
    g_assert(g_hash_table_contains(rules_for_page_1, GINT_TO_POINTER(5)));
}

char* full_input = "47|53\n"
"97|13\n"
"97|61\n"
"97|47\n"
"75|29\n"
"61|13\n"
"75|53\n"
"29|13\n"
"97|29\n"
"53|29\n"
"61|53\n"
"97|53\n"
"61|29\n"
"47|13\n"
"75|47\n"
"97|75\n"
"47|61\n"
"75|61\n"
"47|29\n"
"75|13\n"
"53|13\n"
"\n"
"75,47,61,53,29\n"
"97,61,53,29,13\n"
"75,29,13\n"
"75,97,47,61,53\n"
"61,13,29\n"
"97,13,75,29,47\n";

void get_middle_page_sums_test() {
    char** input_ptr = &input;
    GHashTable* rule_table = build_rule_table(input_ptr);
    MiddlePageSums sums = get_middle_page_sums(*input_ptr, rule_table);
    g_assert_cmpint(sums.correct_ordering_middle_page_sum, ==, 143);
    g_assert_cmpint(sums.reordered_middle_page_sum, ==, 123);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/build_rule_table/build_rule_table", build_rule_table_test);
    g_test_add_func("/get_middle_page_sums/get_middle_page_sums_sum", get_middle_page_sums_test);
    return g_test_run();
}