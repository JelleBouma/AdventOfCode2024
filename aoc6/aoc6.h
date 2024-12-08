#ifndef AOC6_H
#define AOC6_H

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

long count_distinct_positions_in_path(char* map);

#endif //AOC6_H
