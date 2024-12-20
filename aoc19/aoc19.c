#include "aoc19.h"

char** available_patterns;

bool is_possible_design(char* design) {
    if (!*design)
        return true;
    char** pattern_iter = available_patterns;
    while (*pattern_iter) {
        if (starts_with(design, *pattern_iter) && is_possible_design(design + strlen(*pattern_iter)))
            return true;
        pattern_iter++;
    }
    return false;
}

gint64 get_possible_design_count(char* input) {
    char** patterns_and_designs = split_on_empty_lines(input);
    available_patterns = split(patterns_and_designs[0], ", ");
    char** desired_designs = split_lines(patterns_and_designs[1]);
    gint64 possible_design_count = 0;
    while (*desired_designs) {
        if (is_possible_design(*desired_designs))
            possible_design_count++;
        desired_designs++;
    }
    return possible_design_count;
}