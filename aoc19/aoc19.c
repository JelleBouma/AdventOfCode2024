#include "aoc19.h"

HashTree* available_pattern_dict;
char** desired_designs;

gint64 count_possible_options(char* design) {
    if (!*design)
        return 1;
    gint64 possible_options = 0;
    HashNode* node = g_hash_table_lookup(available_pattern_dict, (gconstpointer)(gint64)*design);
    gint64 depth = 1;
    while (node && *(design + depth)) {
        if (node->value)
            possible_options += count_possible_options(design + depth);
        node = g_hash_table_lookup(node->children, (gconstpointer)(gint64)*(design + depth));
        depth++;
    }
    return possible_options;
}

void one_time_setup(char* input) {
    char** patterns_and_designs = split_on_empty_lines(input);
    char** available_patterns = split(patterns_and_designs[0], ", ");
    available_pattern_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    while (*available_patterns) {
        hash_tree_add_str(available_pattern_dict, *available_patterns);
        available_patterns++;
    }
    desired_designs = split_lines(patterns_and_designs[1]);
}

gint64 get_possible_design_count() {
    char** desired_design_iter = desired_designs;
    gint64 possible_design_count = 0;
    while (*desired_design_iter) {
        if (count_possible_options(*desired_design_iter))
            possible_design_count++;
        desired_design_iter++;
    }
    return possible_design_count;
}

gint64 get_possible_option_count() {
    char** desired_design_iter = desired_designs;
    gint64 possible_option_count = 0;
    while (*desired_design_iter) {
        possible_option_count += count_possible_options(*desired_design_iter);
        desired_design_iter++;
    }
    return possible_option_count;
}