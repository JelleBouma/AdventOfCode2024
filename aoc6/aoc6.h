#ifndef AOC6_H
#define AOC6_H

#include <glib.h>

typedef union Pos {
    struct {
        short x;
        short y;
    };
    int as_int;
} Pos;

Pos right(Pos input);
Pos left(Pos input);
Pos up(Pos input);
Pos down(Pos input);

long count_distinct_positions_in_path(char* map);
long count_infinitely_blockable_positions_in_path(char* map);

#endif //AOC6_H
