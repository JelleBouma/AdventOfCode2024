#include "aoc6.h"

#define empty_char '.'
#define guard_char '^'
#define obstacle_char '#'
#define mark_char '!'

gint64 count_distinct_positions_in_path(char* map) {
    int current_direction = 0;
    gint64 distinct_position_count = 1;
    Matrix matrix = new_matrix(map);
    Pos pos = find_in_matrix(matrix, guard_char);
    while (is_in_range(pos, matrix)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos);
        if (next_pos_value == obstacle_char) {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value == empty_char) {
            pos = next_pos;
            distinct_position_count++;
            set_pos_to(matrix, pos, mark_char);
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
    Pos pos = find_in_matrix(matrix, guard_char);
    while (is_in_range(pos, matrix)) {
        Pos next_pos = directions_4[current_direction](pos);
        char next_pos_value = get_from_pos(matrix, next_pos);
        if (next_pos_value == obstacle_char) {
            current_direction++;
            current_direction %= 4;
        }
        else if (next_pos_value && next_pos_value != mark_char) {
            set_pos_to(matrix, next_pos, obstacle_char);
            GHashTable* up_blocks = g_hash_table_new(g_direct_hash, g_direct_equal);
            int inner_direction = (current_direction + 1) % 4;
            Pos inner_pos = pos;
            while (is_in_range(inner_pos, matrix)) {
                Pos inner_next_pos = directions_4[inner_direction](inner_pos);
                char inner_next_pos_value = get_from_pos(matrix, inner_next_pos);
                if (inner_next_pos_value == obstacle_char) {
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
            set_pos_to(matrix, next_pos, mark_char);
            pos = next_pos;
        }
        else
            pos = next_pos;
    }
    return blockable_position_count;
}