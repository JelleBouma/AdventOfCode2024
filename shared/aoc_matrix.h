#ifndef ADVENT_OF_CODE_2024_MATRIX_H
#define ADVENT_OF_CODE_2024_MATRIX_H

#include "aoc_shared_imports.h"
#include "aoc_string.h"
#include "aoc_pos.h"

typedef struct Matrix {
    char** content;
    gint32 x_len;
    gint32 y_len;
} Matrix;

Matrix new_matrix(char* str);
Matrix new_empty_matrix(char default_char, gint32 x_len, gint32 y_len);
char get_from_pos(Matrix matrix, Pos pos);
void set_pos_to(Matrix matrix, Pos pos, char input);
void clear_matrix(Matrix matrix, char default_char);
bool is_in_range(Pos pos, Matrix matrix);
Pos find_in_matrix(Matrix haystack, char needle);
void debug_print_matrix(Matrix matrix);

#endif //ADVENT_OF_CODE_2024_MATRIX_H