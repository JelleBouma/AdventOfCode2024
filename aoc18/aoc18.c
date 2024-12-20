#include "aoc18.h"

#define safe_char '.'
#define corrupted_char '#'
#define start_char 'S'
#define end_char 'E'
#define marked_path_char '0'

gint32* scores;
Matrix memory_space;
gint32 space_x_len;
gint32 space_y_len;

gint32 get_score(Pos pos) {
    return scores[pos.y * space_x_len + pos.x];
}

bool update_score(Pos pos, gint32 new_score) {
    gint32 old_score = scores[pos.y * space_x_len + pos.x];
    if (!old_score || new_score < old_score) {
        scores[pos.y * space_x_len + pos.x] = new_score;
        return true;
    }
    return false;
}

void traverse_path(Pos pos) {
    for (gint32 dd = 0; dd < 4; dd++) {
        gint32 score = get_score(pos);
        Pos next_pos = directions_4[dd](pos);
        char pos_type = get_from_pos(memory_space, next_pos);
        if (pos_type && pos_type != corrupted_char && update_score(next_pos, score + 1))
            traverse_path(next_pos);
    }
}

void one_time_setup(gint32 x_len, gint32 y_len) {
    space_x_len = x_len;
    space_y_len = y_len;
    memory_space = new_empty_matrix(safe_char, x_len, y_len);
    scores = calloc(x_len * y_len, sizeof(gint32));
}

gint32 get_minimum_steps_to_exit_impl(PosList* falling_bytes, gint64 input_limit) {
    PosList* iter = falling_bytes;
    for (gint32 ii = 0; ii < input_limit; ii++) {
        set_pos_to(memory_space, pos_list_get(iter), corrupted_char);
        iter = iter->next;
    }
    Pos start = new_pos(0, 0);
    traverse_path(start);
    gint32 minimum_steps_to_exit = get_score(new_pos(space_x_len - 1, space_y_len - 1));
    memset(scores, 0, space_x_len * space_y_len * sizeof(gint32));
    clear_matrix(memory_space, safe_char);
    return minimum_steps_to_exit;
}


gint32 get_minimum_steps_to_exit(char* input, gint64 input_limit) {
    return get_minimum_steps_to_exit_impl(pos_list_parse(input), input_limit);
}

char* get_first_blocking_byte(char* input) {
    PosList* falling_bytes = pos_list_parse(input);
    gint64 falling_bytes_count = g_list_length(falling_bytes);
    gint64 last_nonblocking = 0;
    gint64 first_blocking = falling_bytes_count - 1;
    while (first_blocking != last_nonblocking + 1) {
        gint64 limit = first_blocking + (last_nonblocking - first_blocking) / 2 + 1;
        gint32 steps_to_exit = get_minimum_steps_to_exit_impl(falling_bytes, limit);
        if (steps_to_exit)
            last_nonblocking = limit - 1;
        else
            first_blocking = limit - 1;

    }
    return pos_to_str(pos_list_index(falling_bytes, first_blocking));
}