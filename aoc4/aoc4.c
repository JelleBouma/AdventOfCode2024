#include <stdbool.h>
#include "aoc4.h"

Pos new_pos(int x, int y) {
    Pos pos = { .x = x, .y = y};
    return pos;
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

long full_word_search_2d(char* needle, char* haystack) {
    long needle_count = 0;
    char** lines = g_strsplit(haystack, "\n", 0);
    needle_count += directional_word_search_2d(needle, lines, right);
    needle_count += directional_word_search_2d(needle, lines, left);
    needle_count += directional_word_search_2d(needle, lines, up);
    needle_count += directional_word_search_2d(needle, lines, down);
    needle_count += directional_word_search_2d(needle, lines, up_left);
    needle_count += directional_word_search_2d(needle, lines, up_right);
    needle_count += directional_word_search_2d(needle, lines, down_left);
    needle_count += directional_word_search_2d(needle, lines, down_right);
    return needle_count;
}

char get_from_pos(char** haystack, Pos pos, int x_lim, int y_lim) {
    if (pos.x < 0 || pos.x >= x_lim || pos.y < 0 || pos.y >= y_lim)
        return '\0';
    else
        return haystack[pos.y][pos.x];
}

long directional_word_search_2d(const char* needle, char** haystack, Pos(*next_pos_func)(Pos)) {
    long needle_count = 0;
    int line_count = 0;
    while (*(haystack + line_count))
        line_count++;
    const int line_len = (int)strlen(*haystack);
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < line_count; pos.y++)
        for (pos.x = 0; pos.x < line_len; pos.x++) {
            int needle_index = 0;
            char hay = get_from_pos(haystack, pos, line_len, line_count);
            Pos next_pos = next_pos_func(pos);
            while (hay && hay == needle[needle_index]) {
                needle_index++;
                if (!needle[needle_index]) {
                    needle_count++;
                    break;
                }
                hay = get_from_pos(haystack, next_pos, line_len, line_count);
                next_pos = next_pos_func(next_pos);
            }
        }
    return needle_count;
}

bool is_valid_for_cross_mas(char diagonal_char) {
    return diagonal_char == 'M' || diagonal_char == 'S';
}

long cross_mas_search_2d(char* haystack) {
    long cross_count = 0;
    char** lines = g_strsplit(haystack, "\n", 0);
    int line_count = 0;
    while (*(lines + line_count))
        line_count++;
    const int line_len = (int)strlen(*lines);
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < line_count; pos.y++)
        for (pos.x = 0; pos.x < line_len; pos.x++) {
            char hay = get_from_pos(lines, pos, line_len, line_count);
            if (hay != 'A')
                continue;
            char up_right_char = get_from_pos(lines, up_right(pos), line_len, line_count);
            if (!is_valid_for_cross_mas(up_right_char))
                continue;
            char up_left_char = get_from_pos(lines, up_left(pos), line_len, line_count);
            if (!is_valid_for_cross_mas(up_left_char))
                continue;
            char down_right_char = get_from_pos(lines, down_right(pos), line_len, line_count);
            if (!is_valid_for_cross_mas(down_right_char))
                continue;
            char down_left_char = get_from_pos(lines, down_left(pos), line_len, line_count);
            if (!is_valid_for_cross_mas(down_left_char))
                continue;
            if (up_right_char == up_left_char && down_left_char == down_right_char && up_right_char != down_right_char)
                cross_count++;
            else if (up_right_char == down_right_char && up_left_char == down_left_char && up_left_char != up_right_char)
                cross_count++;
        }
    return cross_count;
}