#include "aoc18.h"

#define safe_char '.'
#define corrupted_char '#'
#define start_char 'S'
#define end_char 'E'
#define marked_path_char '0'

gint32* scores;
Matrix memory_space;
gint32 space_x_len;

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

void setup(char* input, gint64 input_limit, gint32 x_len, gint32 y_len) {
    space_x_len = x_len;
    memory_space = new_empty_matrix(safe_char, x_len, y_len);
    PosList* falling_bytes = pos_list_parse(input);
    PosList* iter = falling_bytes;
    for (gint32 ii = 0; ii < input_limit; ii++) {
        set_pos_to(memory_space, pos_list_get(iter), corrupted_char);
        iter = iter->next;
    }
}

gint32 get_minimum_steps_to_exit(char* input, gint64 input_limit, gint32 x_len, gint32 y_len) {
    setup(input, input_limit, x_len, y_len);
    Pos start = new_pos(0, 0);
    scores = calloc(x_len * y_len, sizeof(gint32));
    traverse_path(start);
    return get_score(new_pos(x_len - 1, y_len - 1));
}