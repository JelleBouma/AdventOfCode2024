#ifndef AOC4_H
#define AOC4_H

#include <aoc_shared.h>

gint64 full_word_search_2d(char* needle, char* haystack);

gint64 cross_mas_search_2d(char* haystack);

gint64 directional_word_search_2d(const char* needle, Matrix haystack, Pos(*next_pos_func)(Pos));

#endif //AOC4_H
