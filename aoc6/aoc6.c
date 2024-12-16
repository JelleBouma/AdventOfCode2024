#include "aoc6.h"

Pos find_guard(Matrix matrix) {
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            if (get_from_pos(matrix, pos) == '^')
                return pos;
        }
    exit(EXIT_FAILURE);
}

gint64 count_distinct_positions_in_path(char* map) {
    int current_direction = 0;
    gint64 distinct_position_count = 1;
    Matrix matrix = new_matrix(map);
    Pos pos = find_guard(matrix);
    while (is_in_range(pos, matrix)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos);
        if (next_pos_value == '#') {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value == '.') {
            pos = next_pos;
            distinct_position_count++;
            set_pos_to(matrix, pos, '^'); // mark as counted
        }
        else
            pos = next_pos;
    }
    return distinct_position_count;
}

gint64 count_infinitely_blockable_positions_in_path(char* map) {
    int current_direction = 0;
    gint64 blockable_position_count = 0;
    Matrix matrix = new_matrix(map);
    Pos pos = find_guard(matrix);
    while (is_in_range(pos, matrix)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos);
        if (next_pos_value == '#') {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value && next_pos_value != '!') {
            set_pos_to(matrix, next_pos, '#');
            GHashTable* up_blocks = g_hash_table_new(g_direct_hash, g_direct_equal);
            int inner_direction = (current_direction + 1) % 4;
            Pos inner_pos = pos;
            while (is_in_range(inner_pos, matrix)) {
                Pos inner_next_pos = directions_4[inner_direction](inner_pos);
                char inner_next_pos_value = get_from_pos(matrix, inner_next_pos);
                if (inner_next_pos_value == '#') {
                    if (inner_direction == 0) {
                        if (g_hash_table_contains(up_blocks, GINT_TO_POINTER(inner_next_pos.as_int))) {
                            blockable_position_count++;
                            break;
                        }
                        else
                            g_hash_table_insert(up_blocks, GINT_TO_POINTER(inner_next_pos.as_int), NULL);
                    }
                    inner_direction++;
                    inner_direction %= 4;
                }
                else
                    inner_pos = inner_next_pos;
            }
            g_hash_table_destroy(up_blocks);
            set_pos_to(matrix, next_pos, '!'); // mark as counted
            pos = next_pos;
        }
        else
            pos = next_pos;
    }
    return blockable_position_count;
}