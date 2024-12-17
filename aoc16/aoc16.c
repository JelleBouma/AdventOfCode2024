#include "aoc16.h"

#define empty_char '.'
#define wall_char '#'
#define start_char 'S'
#define end_char 'E'

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
    int score = get_score(pos, dir);
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

gint32 get_best_score_from_array(Pos end) {
    gint32 best_score = G_MAXINT32;
    for (int dd = 0; dd < 4; dd++) {
        gint32 score = get_score(end, dd);
        if (score && score < best_score)
            best_score = score;
    }
    return best_score;
}

gint64 get_best_path_score(char* maze_string) {
    maze = new_matrix(maze_string);
    maze_x_len = maze.x_len;
    Pos start = find_in_matrix(maze, start_char);
    Pos end = find_in_matrix(maze, end_char);
    scores = calloc(maze.y_len * maze_x_len * 4, sizeof(gint32));
    traverse_path(start, 1);
    return get_best_score_from_array(end);
}