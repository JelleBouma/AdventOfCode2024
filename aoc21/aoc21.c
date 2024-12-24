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

GString* get_sequence(char* code, Matrix keys) {
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
    return sequence;
}

gint64 get_length_of_shortest_sequence(char* code) {
    GString* keypad_sequence = get_sequence(code, keypad);
    for (gint32 kk = 0; kk < directional_keypad_count; kk++)
        keypad_sequence = get_sequence(keypad_sequence->str, directional_keypad);
    return (gint64)keypad_sequence->len;
}

gint64 get_complexity(char* code) {
    Int64List* numerics = int_list_parse(code);
    gint64 numeric = int_list_get(numerics);
    g_list_free(numerics);
    return get_length_of_shortest_sequence(code) * numeric;
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