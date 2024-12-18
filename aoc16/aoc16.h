#ifndef AOC16_H
#define AOC16_H

#include <aoc_shared.h>

void init_path_traverse(char* maze_string);
gint64 get_best_path_score();
gint32 get_best_paths_tile_count();

#endif //AOC16_H