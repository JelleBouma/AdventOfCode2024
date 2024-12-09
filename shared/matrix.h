#ifndef ADVENT_OF_CODE_2024_MATRIX_H
#define ADVENT_OF_CODE_2024_MATRIX_H

#include "pos.h"
#include <glib.h>

typedef struct Matrix {
    char** content;
    short x_len;
    short y_len;
} Matrix;

Matrix new_matrix(char* str);

char get_from_pos(Matrix matrix, Pos pos);
void set_pos_to(Matrix matrix, Pos pos, char input);

#endif //ADVENT_OF_CODE_2024_MATRIX_H