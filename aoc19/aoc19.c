#include "aoc19.h"

HashTree* available_pattern_dict;
char** desired_designs;

gint64 count_possible_options(char* design) {
    gint64 full_len = (gint64)strlen(design);
    gint64 options[full_len];
    for (gint32 oo = 0; oo < full_len; oo++)
        options[oo] = 0;
    for (gint32 offset = 0; offset < full_len; offset++) {
        HashNode* node = g_hash_table_lookup(available_pattern_dict, (gconstpointer)(gint64)*(design + offset));
        gint32 depth = 0;
        while (node) {
            if (node->value) {
                if (offset == 0)
                    options[depth] = 1;
                else
                    options[offset + depth] += options[offset - 1];
            }
            depth++;
            node = g_hash_table_lookup(node->children, (gconstpointer)(gint64)*(design + offset + depth));
        }
    }
    return options[full_len - 1];
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