#include <stdbool.h>
#include "aoc6.h"

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
    int current_direction = 0;
    long distinct_position_count = 1;
    int line_count = 0;
    char** matrix = g_strsplit(map, "\n", 0);
    while (*(matrix + line_count))
        line_count++;
    const int line_len = (int)strlen(*matrix);
    Pos pos = find_guard(matrix, line_len, line_count);
    while (is_in_range(pos, line_len, line_count)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos, line_len, line_count);
        if (next_pos_value == '#') {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value == '.') {
            pos = next_pos;
            distinct_position_count++;
            set_pos_to(matrix, pos, line_len, line_count, '^'); // mark as counted
        }
        else
            pos = next_pos;
    }
    return distinct_position_count;
}

long count_infinitely_blockable_positions_in_path(char* map) {
    int current_direction = 0;
    long blockable_position_count = 0;
    int line_count = 0;
    char** matrix = g_strsplit(map, "\n", 0);
    while (*(matrix + line_count))
        line_count++;
    const int line_len = (int)strlen(*matrix);
    Pos pos = find_guard(matrix, line_len, line_count);
    while (is_in_range(pos, line_len, line_count)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos, line_len, line_count);
        if (next_pos_value == '#') {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value && next_pos_value != '!') {
            set_pos_to(matrix, next_pos, line_len, line_count, '#');
            GHashTable* up_blocks = g_hash_table_new(g_direct_hash, g_direct_equal);
            int inner_direction = (current_direction + 1) % 4;
            Pos inner_pos = pos;
            while (is_in_range(inner_pos, line_len, line_count)) {
                Pos inner_next_pos = directions_4[inner_direction](inner_pos);
                char inner_next_pos_value = get_from_pos(matrix, inner_next_pos, line_len, line_count);
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
            set_pos_to(matrix, next_pos, line_len, line_count, '!'); // mark as counted
            pos = next_pos;
        }
        else
            pos = next_pos;
    }
    return blockable_position_count;
}