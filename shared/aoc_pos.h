#ifndef ADVENT_OF_CODE_2024_POS_H
#define ADVENT_OF_CODE_2024_POS_H

#include "aoc_shared_imports.h"

typedef union {
    struct {
        gint32 x;
        gint32 y;
    };
    gint64 as_int;
} Pos;

Pos plus(Pos a, Pos b);
Pos minus(Pos a, Pos b);
Pos mul(Pos a, Pos b);
Pos mod(Pos a, Pos b);

Pos new_pos(gint32 x, gint32 y);
Pos right(Pos input);
Pos left(Pos input);
Pos up(Pos input);
Pos down(Pos input);
Pos up_left(Pos input);
Pos up_right(Pos input);
Pos down_left(Pos input);
Pos down_right(Pos input);
GHashTable* get_char_direction_dict();
char* pos_to_str(Pos pos);

extern Pos(*directions_4[4])(Pos);
extern Pos(*directions_8[8])(Pos);


#endif //ADVENT_OF_CODE_2024_POS_H
