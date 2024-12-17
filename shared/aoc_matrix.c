#include "aoc_matrix.h"

Matrix new_matrix(char* str) {
    short line_count = 0;
    char** content = split_lines(str);
    while (*(content + line_count))
        line_count++;
    const short line_len = (short)strlen(*content);
    Matrix matrix = { .content = content, .x_len = line_len, .y_len = line_count };
    return matrix;
}

char get_from_pos(Matrix matrix, Pos pos) {
    if (!is_in_range(pos, matrix))
        return '\0';
    else
        return matrix.content[pos.y][pos.x];
}

void set_pos_to(Matrix matrix, Pos pos, char input) {
    if (is_in_range(pos, matrix))
        matrix.content[pos.y][pos.x] = input;
}

void clear_matrix(Matrix matrix) {
    for (int yy = 0; yy < matrix.y_len; yy++)
        for (int xx = 0; xx < matrix.x_len; xx++)
            matrix.content[yy][xx] = 0;
}

bool is_in_range(Pos pos, Matrix matrix) {
    return pos.x >= 0 && pos.x < matrix.x_len && pos.y >= 0 && pos.y < matrix.y_len;
}

Pos find_in_matrix(Matrix haystack, char needle) {
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < haystack.y_len; pos.y++)
        for (pos.x = 0; pos.x < haystack.x_len; pos.x++) {
            if (get_from_pos(haystack, pos) == needle)
                return pos;
        }
    return new_pos(-1, -1);
}

void debug_print_matrix(Matrix matrix) {
    char** lines = matrix.content;
    while (*lines) {
        g_test_message("%s", *lines);
        lines++;
    }
    g_test_message("\n");
}