#ifndef AOC14_H
#define AOC14_H

#include "../shared/aoc_pos.h"
#include "../shared/aoc_int_list.h"

gint64 get_safety_factor(char* robots, gint32 x_tiles, gint32 y_tiles, gint64 move_count);
gint64 get_seconds_to_lowest_safety_factor(char* robots, gint32 x_tiles, gint32 y_tiles);
gint64 get_seconds_to_tree(char* robots, gint32 x_tiles, gint32 y_tiles);

#endif //AOC14_H