#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aoc5.h"

void get_middle_page_total_from_file(FILE* file) {
    // read entire file into buffer
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char buffer[file_size + 1];
    char* buffer_ptr = buffer;
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = 0;
    fclose(file);

    GHashTable* rule_table = build_rule_table(&buffer_ptr);
    long middle_page_total = get_middle_page_total(buffer_ptr, rule_table);
    printf("middle page total: %ld", middle_page_total);
}

GHashTable* build_rule_table(char** str) {
    GHashTable* rule_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    char* current_line = *str;
    while (current_line && *current_line != '\n' && *current_line != '\r') {
        char* next_line = strchr(current_line, '\n');
        long before_page = strtol(current_line, &current_line, page_base);
        long after_page = strtol(current_line + 1, &current_line, page_base);
        if (!g_hash_table_contains(rule_table, GINT_TO_POINTER(before_page)))
            g_hash_table_insert(rule_table, GINT_TO_POINTER(before_page), g_hash_table_new(g_direct_hash, g_direct_equal));
        g_hash_table_insert(g_hash_table_lookup(rule_table, GINT_TO_POINTER(before_page)), GINT_TO_POINTER(after_page), NULL);
        if (next_line)
            current_line = next_line + 1;
    }
    while (*current_line == '\r' || *current_line == '\n')
        current_line++;
    *str = current_line;
    return rule_table;
}

bool has_remaining_updates(const char* str) {
    return str && *str && *str != '\n' && *str != '\r';
}

long get_middle_page_total(char* updates, GHashTable* rule_table) {
    long middle_page_total = 0;
    char* current_line = updates;
    while (has_remaining_updates(current_line)) {
        int is_correct_order = true;
        GList* pages = NULL;
        while (has_remaining_updates(current_line)) {
            if (*current_line == ',')
                current_line++;
            long page = strtol(current_line, &current_line, page_base);
            if (g_hash_table_contains(rule_table, GINT_TO_POINTER(page))) {
                GHashTable* rules = g_hash_table_lookup(rule_table, GINT_TO_POINTER(page));
                int page_count = g_list_length(pages);
                for (int pp = 0; pp < page_count; pp++)
                    if (g_hash_table_contains(rules, g_list_nth_data(pages, pp))) {
                        is_correct_order = false;
                        break;
                    }
            }
            if (!is_correct_order)
                break;
            pages = g_list_append(pages, GINT_TO_POINTER(page));
        }
        if (is_correct_order)
            middle_page_total += g_list_nth_data(pages, g_list_length(pages) / 2);
        g_list_free(pages);
        char* next_line = strchr(current_line, '\n');
        current_line = next_line ? next_line + 1 : NULL;
    }
    return middle_page_total;
}