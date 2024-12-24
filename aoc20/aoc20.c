#include "aoc20.h"

#define empty_char '.'
#define wall_char '#'
#define start_char 'S'
#define end_char 'E'

gint32* scores;
Matrix track;

gint32 get_score(Pos pos, gint32* score_table) {
    return score_table[pos.y * track.x_len + pos.x];
}

bool update_score(Pos pos, gint32* score_table, gint32 new_score) {
    gint32 old_score = get_score(pos, score_table);
    gint32 old_score_no_cheating = get_score(pos, scores);
    if ((!old_score_no_cheating || new_score <= old_score_no_cheating) && (!old_score || new_score < old_score)) {
        score_table[pos.y * track.x_len + pos.x] = new_score;
        return true;
    }
    return false;
}

void traverse_path(Pos start_pos, gint32* score_table) {
    PosList* list_start = NULL;
    pos_list_prepend(&list_start, start_pos);
    PosList* list_end = list_start;
    while (list_end) {
        Pos pos = pos_list_get(list_end);
        for (gint32 dd = 0; dd < 4; dd++) {
            gint32 score = get_score(pos, score_table);
            Pos next_pos = directions_4[dd](pos);
            char pos_type = get_from_pos(track, next_pos);
            if (pos_type && pos_type != wall_char && update_score(next_pos, score_table, score + 1))
                pos_list_prepend(&list_start, next_pos);
        }
        list_end = g_list_delete_link(list_end->prev, list_end);
    }
}

void setup(char* track_string) {
    track = new_matrix(track_string);
    scores = calloc(track.y_len * track.x_len, sizeof(gint32));
    traverse_path(find_in_matrix(track, start_char), scores);
}

gint64 get_count_of_cheats_that_save_x_from_pos(Pos pos, gint32 cheat_time, gint32 to_save) {
    gint64 res = 0;
    gint32 score = get_score(pos, scores);
    Pos pos_to_check;
    for (pos_to_check.y = pos.y - cheat_time; pos_to_check.y <= pos.y + cheat_time; pos_to_check.y++)
        for (pos_to_check.x = pos.x - cheat_time; pos_to_check.x <= pos.x + cheat_time; pos_to_check.x++) {
            gint32 dist = manhattan_dist(pos, pos_to_check);
            if (dist < 2 || dist > cheat_time)
                continue;
            char pos_type = get_from_pos(track, pos_to_check);
            if (!pos_type || pos_type == wall_char)
                continue;
            gint32 cheated_score = score + dist;
            if (cheated_score <= get_score(pos_to_check, scores) - to_save)
                res++;
        }
    return res;
}

gint64 get_count_of_cheats_that_save_x(gint32 cheat_time, gint32 to_save) {
    gint64 count_of_cheats_that_save_x_secs = 0;
    Pos pos;
    for (pos.y = 0; pos.y < track.y_len; pos.y++)
        for (pos.x = 0; pos.x < track.x_len; pos.x++)
            if (get_from_pos(track, pos) != wall_char)
                count_of_cheats_that_save_x_secs += get_count_of_cheats_that_save_x_from_pos(pos, cheat_time, to_save);
    return count_of_cheats_that_save_x_secs;
}