#include "aoc5.h"

MiddlePageSums get_middle_page_total(char* input) {
    char** split_input = split_on_empty_lines(input);
    GHashTable* rule_table = build_rule_table(split_input[0]);
    return get_middle_page_sums(split_input[1], rule_table);
}

GHashTable* build_rule_table(char* str) {
    GHashTable* rule_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    char* current_line = str;
    while (*current_line && *current_line != '\n' && *current_line != '\r') {
        char* next_line = strchr(current_line, '\n');
        gint64 before_page = strtol(current_line, &current_line, decimal_base);
        gint64 after_page = strtol(current_line + 1, &current_line, decimal_base);
        if (!g_hash_table_contains(rule_table, GINT_TO_POINTER(before_page)))
            g_hash_table_insert(rule_table, GINT_TO_POINTER(before_page), g_hash_table_new(g_direct_hash, g_direct_equal));
        g_hash_table_insert(g_hash_table_lookup(rule_table, GINT_TO_POINTER(before_page)), GINT_TO_POINTER(after_page), NULL);
        if (next_line)
            current_line = next_line + 1;
    }
    if (*current_line == '\r' || *current_line == '\n')
        current_line++;
    return rule_table;
}

bool has_remaining_updates(const char* str) {
    return str && *str && *str != '\n' && *str != '\r';
}

MiddlePageSums get_middle_page_sums(char* updates, GHashTable* rule_table) {
    gint64 correct_order_middle_page_sum = 0;
    gint64 reordered_middle_page_sum = 0;
    char* current_line = updates;
    while (has_remaining_updates(current_line)) {
        bool is_correct_order = true;
        GList* pages = NULL;
        while (has_remaining_updates(current_line)) {
            if (*current_line == ',')
                current_line++;
            gint64 page = strtol(current_line, &current_line, decimal_base);
            bool is_reordered = false;
            if (g_hash_table_contains(rule_table, GINT_TO_POINTER(page))) {
                GHashTable* rules = g_hash_table_lookup(rule_table, GINT_TO_POINTER(page));
                int page_count = g_list_length(pages);
                for (int pp = 0; pp < page_count; pp++)
                {
                    GList* element_to_check = g_list_nth(pages, pp);
                    gint64 page_to_check = GPOINTER_TO_INT(g_list_nth_data(element_to_check, 0));
                    is_reordered = g_hash_table_contains(rules, GINT_TO_POINTER(page_to_check));
                    if (is_reordered)
                    {
                        is_correct_order = false;
                        pages = g_list_insert_before(pages, element_to_check, GINT_TO_POINTER(page));
                        break;
                    }
                }
            }
            if (!is_reordered)
                pages = g_list_append(pages, GINT_TO_POINTER(page));
        }
        gint64 middle_page = GPOINTER_TO_INT(g_list_nth_data(pages, g_list_length(pages) / 2));
        if (is_correct_order)
            correct_order_middle_page_sum += middle_page;
        else
            reordered_middle_page_sum += middle_page;
        g_list_free(pages);
        char* next_line = strchr(current_line, '\n');
        current_line = next_line && *next_line ? next_line + 1 : NULL;
    }
    MiddlePageSums sums;
    sums.correct_ordering_middle_page_sum = correct_order_middle_page_sum;
    sums.reordered_middle_page_sum = reordered_middle_page_sum;
    return sums;
}