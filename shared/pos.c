#include "pos.h"

Pos new_pos(short x, short y) {
    Pos pos = { .x = x, .y = y};
    return pos;
}

Pos plus(Pos a, Pos b) {
    return new_pos(a.x + b.x, a.y + b.y);
}
Pos minus(Pos a, Pos b) {
    return new_pos(a.x - b.x, a.y - b.y);
}
Pos mul(Pos a, Pos b) {
    return new_pos(a.x * b.x, a.y * b.y);
}

Pos right(Pos input) {
    return new_pos(input.x + 1, input.y);
}

Pos left(Pos input) {
    return new_pos(input.x - 1, input.y);
}

Pos up(Pos input) {
    return new_pos(input.x, input.y - 1);
}

Pos down(Pos input) {
    return new_pos(input.x, input.y + 1);
}

Pos up_left(Pos input) {
    return up(left(input));
}

Pos up_right(Pos input) {
    return up(right(input));
}

Pos down_left(Pos input) {
    return down(left(input));
}

Pos down_right(Pos input) {
    return down(right(input));
}

Pos(*directions_4[4])(Pos) = { up, right, down, left };
Pos(*directions_8[8])(Pos) = { up, right, down, left, up_left, up_right, down_left, down_right };