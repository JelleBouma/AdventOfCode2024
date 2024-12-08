#ifndef AOC2_AOC4_H
#define AOC2_AOC4_H

#include <glib.h>

typedef struct Pos {
    int x;
    int y;
} Pos;

Pos right(Pos input);
Pos left(Pos input);
Pos up(Pos input);
Pos down(Pos input);
Pos up_left(Pos input);
Pos up_right(Pos input);
Pos down_left(Pos input);
Pos down_right(Pos input);

long full_word_search_2d(char* needle, char* haystack);

long cross_mas_search_2d(char* haystack);

long directional_word_search_2d(const char* needle, char** haystack, Pos(*next_pos_func)(Pos));

#endif //AOC2_AOC4_H
