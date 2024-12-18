#include "aoc16.h"

#define empty_char '.'
#define wall_char '#'
#define start_char 'S'
#define end_char 'E'
#define marked_path_char '0'

gint32* scores;
Matrix maze;
gint32 maze_x_len;

gint32 get_score(Pos pos, gint32 direction) {
    return scores[pos.y * maze_x_len * 4 + pos.x * 4 + direction];
}

bool update_score(Pos pos, gint32 direction, gint32 new_score) {
    gint32 old_score = scores[pos.y * maze_x_len * 4 + pos.x * 4 + direction];
    if (!old_score || new_score < old_score) {
        scores[pos.y * maze_x_len * 4 + pos.x * 4 + direction] = new_score;
        return true;
    }
    return false;
}

void traverse_path(Pos pos, gint32 dir) {
    gint32 score = get_score(pos, dir);
    Pos next_pos = directions_4[dir](pos);
    if (get_from_pos(maze, next_pos) != wall_char && update_score(next_pos, dir, score + 1)) {
        traverse_path(next_pos, dir);
    }
    gint32 clock_dir = (dir + 1) % 4;
    Pos clock_pos = directions_4[clock_dir](pos);
    if (get_from_pos(maze, clock_pos) != wall_char && update_score(clock_pos, clock_dir, score + 1001))
        traverse_path(clock_pos, clock_dir);
    gint32 counter_clock_dir = (dir + 3) % 4;
    Pos counter_clock_pos = directions_4[counter_clock_dir](pos);
    if (get_from_pos(maze, counter_clock_pos) != wall_char && update_score(counter_clock_pos, counter_clock_dir, score + 1001))
        traverse_path(counter_clock_pos, counter_clock_dir);
}

gint32 get_best_score_from_array(Pos pos) {
    gint32 best_score = G_MAXINT32;
    for (int dd = 0; dd < 4; dd++) {
        gint32 score = get_score(pos, dd);
        if (score && score < best_score)
            best_score = score;
    }
    return best_score;
}

void traverse_back_path(Pos end_pos) {
    PosList* pos_list = NULL;
    pos_list_prepend(&pos_list, end_pos);
    while (pos_list) {
        Pos pos = pos_list_get(pos_list);
        pos_list = g_list_delete_link(pos_list, pos_list);
        gint32 best_score = get_best_score_from_array(pos);
        set_pos_to(maze, pos, marked_path_char);
        for (gint32 dd = 0; dd < 4; dd++) {
            gint32 score = get_score(pos, dd);
            if (score == best_score) {
                Pos(*move_back)(Pos) = directions_4[(dd + 2) % 4];
                Pos back = move_back(pos);
                Pos double_back = move_back(back);
                if (get_from_pos(maze, back) != marked_path_char) {
                    if (get_score(back, dd) == score - 1)
                        pos_list_prepend(&pos_list, back);
                    else if (get_score(back, (dd + 1) % 4) == score - 1001)
                        pos_list_prepend(&pos_list, back);
                    else if (get_score(back, (dd + 3) % 4) == score - 1001)
                        pos_list_prepend(&pos_list, back);
                }
                if (get_from_pos(maze, double_back) != marked_path_char && get_score(double_back, dd) == score - 2)
                    pos_list_prepend(&pos_list, double_back);
            }
        }
    }
}

void init_path_traverse(char* maze_string) {
    maze = new_matrix(maze_string);
    maze_x_len = maze.x_len;
    Pos start = find_in_matrix(maze, start_char);
    scores = calloc(maze.y_len * maze_x_len * 4, sizeof(gint32));
    traverse_path(start, 1);
}

gint64 get_best_path_score() {
    Pos end = find_in_matrix(maze, end_char);
    return get_best_score_from_array(end);
}

gint32 get_best_paths_tile_count() {
    Pos end = find_in_matrix(maze, end_char);
    traverse_back_path(end);
    gint32 best_path_tile_count = 0;
    Pos pos;
    for (pos.x = 0; pos.x < maze.x_len; pos.x++)
        for (pos.y = 0; pos.y < maze.y_len; pos.y++)
            if (get_from_pos(maze, pos) == marked_path_char)
                best_path_tile_count++;
    return best_path_tile_count;
}