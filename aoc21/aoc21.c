#include "aoc21.h"

char* keypad_str = "789\n"
                   "456\n"
                   "123\n"
                   ".0A";

char* directional_keypad_str = ".^A\n"
                               "<v>";

Matrix keypad;
Matrix directional_keypad;
gint32 directional_keypad_count;

void setup() {
    keypad = new_matrix(keypad_str);
    directional_keypad = new_matrix(directional_keypad_str);
}

char* get_sequence(char* code, Matrix keys) {
    Pos pos = find_in_matrix(keys, 'A');
    GString* sequence = g_string_new("");
    while (*code) {
        Pos target = find_in_matrix(keys, *code);
        while (pos.x != target.x || pos.y != target.y) {
            if (get_from_pos(keys, new_pos(target.x, pos.y)) != '.')
                for (; pos.x > target.x; pos.x--)
                    g_string_append(sequence, "<");
            if (get_from_pos(keys, new_pos(pos.x, target.y)) != '.') {
                for (; pos.y > target.y; pos.y--)
                    g_string_append(sequence, "^");
                for (; pos.y < target.y; pos.y++)
                    g_string_append(sequence, "v");
            }
            for (; pos.x < target.x; pos.x++)
                g_string_append(sequence, ">");
        }
        g_string_append(sequence, "A");
        code++;
    }
    return sequence->str;
}

gint64 get_total_len(HashCounts* counts) {
    gint64 res = 0;
    GHashTableIter iter;
    g_hash_table_iter_init(&iter, counts);
    char* seq_part;
    while (g_hash_table_iter_next(&iter, (gpointer*)&seq_part, NULL)) {
        gint64 count = get_count(counts, seq_part);
        res += count * (gint64)strlen(seq_part);
    }
    return res;
}

HashCounts* get_counts(char* seq) {
    HashCounts* counts = g_hash_table_new(g_str_hash, g_str_equal);
    GString* seq_part = g_string_new("");
    while (*seq) {
        g_string_append_c(seq_part, *seq);
        if (*seq == 'A') {
            hash_count_add(counts, seq_part->str, 1);
            seq_part = g_string_new("");
        }
        seq++;
    }
    return counts;
}

char** split_seq(char* seq) {
    char** split = g_strsplit(seq, "A", 0);
    char** split_iter = split;
    while (*(split_iter + 1)) {
        *split_iter = g_strconcat(*split_iter, "A", NULL);
        split_iter++;
    }
    return split;
}

gint64 get_length_of_shortest_sequence(char* code) {
    char* keypad_sequence = get_sequence(code, keypad);
    HashCounts* counts = get_counts(keypad_sequence);
    HashCounts* new_counts;
    GHashTable* translation_table = g_hash_table_new(g_str_hash, g_str_equal);
    for (gint32 kk = 0; kk < directional_keypad_count; kk++) {
        new_counts = g_hash_table_new(g_str_hash, g_str_equal);
        GHashTableIter iter;
        g_hash_table_iter_init(&iter, counts);
        char* seq_part;
        while (g_hash_table_iter_next(&iter, (gpointer*)&seq_part, NULL)) {
            gint64 count = get_count(counts, seq_part);
            if (count < 0)
                exit(666);
            char** sub_seqs = g_hash_table_lookup(translation_table, seq_part);
            if (!sub_seqs) {
                sub_seqs = split_seq(get_sequence(seq_part, directional_keypad));
                g_hash_table_insert(translation_table, seq_part, sub_seqs);
            }
            while (*sub_seqs) {
                hash_count_add(new_counts, *sub_seqs, count);
                sub_seqs++;
            }
        }
        counts = new_counts;
    }
    return get_total_len(counts);
}

gint64 get_complexity(char* code) {
    Int64List* numerics = int_list_parse(code);
    gint64 numeric = int_list_get(numerics);
    g_list_free(numerics);
    gint64 shortest_seq_len = get_length_of_shortest_sequence(code);
    return shortest_seq_len * numeric;
}

gint64 get_sum_of_complexities(char* input, gint32 directional_keypads) {
    setup();
    directional_keypad_count = directional_keypads;
    gint64 res = 0;
    char** codes = split_lines(input);
    while (*codes) {
        res += get_complexity(*codes);
        codes++;
    }
    return res;
}