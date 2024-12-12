#ifndef ADVENT_OF_CODE_2024_POS_H
#define ADVENT_OF_CODE_2024_POS_H

#include <stdbool.h>

typedef union Pos {
    struct {
        short x;
        short y;
    };
    int as_int;
} Pos;

Pos plus(Pos a, Pos b);
Pos minus(Pos a, Pos b);
Pos mul(Pos a, Pos b);

Pos new_pos(short x, short y);
Pos right(Pos input);
Pos left(Pos input);
Pos up(Pos input);
Pos down(Pos input);
Pos up_left(Pos input);
Pos up_right(Pos input);
Pos down_left(Pos input);
Pos down_right(Pos input);

extern Pos(*directions_4[4])(Pos);
extern Pos(*directions_8[8])(Pos);

#endif //ADVENT_OF_CODE_2024_POS_H
