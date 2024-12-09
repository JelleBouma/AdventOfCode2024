#ifndef AOC4_H
#define AOC4_H

#include <glib.h>
#include "../shared/matrix.h"

long full_word_search_2d(char* needle, char* haystack);

long cross_mas_search_2d(char* haystack);

long directional_word_search_2d(const char* needle, Matrix haystack, Pos(*next_pos_func)(Pos));

#endif //AOC4_H
