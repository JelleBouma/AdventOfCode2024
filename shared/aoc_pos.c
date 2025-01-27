#include "aoc_pos.h"

Pos new_pos(gint32 x, gint32 y) {
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
Pos mod(Pos a, Pos b) {
    return new_pos(a.x % b.x, a.y % b.y);
}
gint32 manhattan_dist(Pos a, Pos b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
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

GHashTable* get_char_direction_dict() {
    GHashTable* char_direction_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(char_direction_dict, GINT_TO_POINTER('^'), up);
    g_hash_table_insert(char_direction_dict, GINT_TO_POINTER('>'), right);
    g_hash_table_insert(char_direction_dict, GINT_TO_POINTER('v'), down);
    g_hash_table_insert(char_direction_dict, GINT_TO_POINTER('<'), left);
    return char_direction_dict;
}

GHashTable* get_direction_char_dict() {
    GHashTable* direction_char_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(direction_char_dict, up, GINT_TO_POINTER('^'));
    g_hash_table_insert(direction_char_dict, right, GINT_TO_POINTER('>'));
    g_hash_table_insert(direction_char_dict, down, GINT_TO_POINTER('v'));
    g_hash_table_insert(direction_char_dict, left, GINT_TO_POINTER('<'));
    return direction_char_dict;
}

char* pos_to_str(Pos pos) {
    return g_strdup_printf("%d,%d", pos.x, pos.y);
}

Pos(*directions_4[4])(Pos) = { up, right, down, left };
Pos(*directions_8[8])(Pos) = { up, right, down, left, up_left, up_right, down_left, down_right };