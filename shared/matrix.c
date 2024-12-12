#include "matrix.h"

Matrix new_matrix(char* str) {
    short line_count = 0;
    char** content = g_strsplit(str, "\r\n", 0);
    if (strlen(str) == strlen(*content))
        content = g_strsplit(str, "\n", 0);
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