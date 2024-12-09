#include "pos.h"

Pos new_pos(short x, short y) {
    Pos pos = { .x = x, .y = y};
    return pos;
}

Pos right(Pos input) {
    return new_pos(input.x + 1, input.y);
}

Pos left(Pos input) {
    return new_pos(input.x - 1, input.y);
}

Pos up(Pos input) {
    return new_pos(input.x, input.y - 1);
}

Pos down(Pos input) {
    return new_pos(input.x, input.y + 1);
}

Pos up_left(Pos input) {
    return up(left(input));
}

Pos up_right(Pos input) {
    return up(right(input));
}

Pos down_left(Pos input) {
    return down(left(input));
}

Pos down_right(Pos input) {
    return down(right(input));
}

Pos(*directions_4[4])(Pos) = { up, right, down, left };
Pos(*directions_8[8])(Pos) = { up, right, down, left, up_left, up_right, down_left, down_right };

bool is_in_range(Pos pos, int x_lim, int y_lim) {
    return pos.x >= 0 && pos.x < x_lim && pos.y >= 0 && pos.y < y_lim;
}

char get_from_pos(char** matrix, Pos pos, int x_lim, int y_lim) {
    if (!is_in_range(pos, x_lim, y_lim))
        return '\0';
    else
        return matrix[pos.y][pos.x];
}

void set_pos_to(char** matrix, Pos pos, int x_lim, int y_lim, char input) {
    if (is_in_range(pos, x_lim, y_lim))
        matrix[pos.y][pos.x] = input;
}