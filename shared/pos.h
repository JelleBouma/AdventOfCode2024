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

bool is_in_range(Pos pos, int x_lim, int y_lim);
char get_from_pos(char** matrix, Pos pos, int x_lim, int y_lim);
void set_pos_to(char** matrix, Pos pos, int x_lim, int y_lim, char input);

#endif //ADVENT_OF_CODE_2024_POS_H
