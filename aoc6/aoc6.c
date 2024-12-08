#include <stdbool.h>
#include "aoc6.h"

Pos new_pos(int x, int y) {
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

Pos find_guard(char** matrix, const int line_len, const int line_count) {
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < line_count; pos.y++)
        for (pos.x = 0; pos.x < line_len; pos.x++) {
            if (get_from_pos(matrix, pos, line_len, line_count) == '^')
                return pos;
        }
    exit(EXIT_FAILURE);
}

long count_distinct_positions_in_path(char* map) {
    Pos(*directions[4])(Pos) = { up, right, down, left };
    int current_direction = 0;
    long distinct_position_count = 1;
    int line_count = 0;
    char** matrix = g_strsplit(map, "\n", 0);
    while (*(matrix + line_count))
        line_count++;
    const int line_len = (int)strlen(*matrix);
    Pos pos = find_guard(matrix, line_len, line_count);
    while (is_in_range(pos, line_len, line_count)) {
        Pos next_pos = directions[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos, line_len, line_count);
        if (next_pos_value == '#') {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value == '.') {
            pos = next_pos;
            distinct_position_count++;
            set_pos_to(matrix, pos, line_len, line_count, '^');
        }
        else
            pos = next_pos;
    }
    return distinct_position_count;
}