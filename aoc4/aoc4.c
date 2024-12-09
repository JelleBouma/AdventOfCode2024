#include <stdbool.h>
#include "aoc4.h"

long full_word_search_2d(char* needle, char* haystack) {
    long needle_count = 0;
    char** lines = g_strsplit(haystack, "\n", 0);
    for (int dd = 0; dd < 8; dd ++)
        needle_count += directional_word_search_2d(needle, lines, directions_8[dd]);
    return needle_count;
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