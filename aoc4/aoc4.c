#include <stdbool.h>
#include "aoc4.h"

gint64 full_word_search_2d(char* needle, char* haystack) {
    gint64 needle_count = 0;
    Matrix matrix = new_matrix(haystack);
    for (int dd = 0; dd < 8; dd ++)
        needle_count += directional_word_search_2d(needle, matrix, directions_8[dd]);
    return needle_count;
}

gint64 directional_word_search_2d(const char* needle, Matrix haystack, Pos(*next_pos_func)(Pos)) {
    gint64 needle_count = 0;
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < haystack.y_len; pos.y++)
        for (pos.x = 0; pos.x < haystack.x_len; pos.x++) {
            int needle_index = 0;
            char hay = get_from_pos(haystack, pos);
            Pos next_pos = next_pos_func(pos);
            while (hay && hay == needle[needle_index]) {
                needle_index++;
                if (!needle[needle_index]) {
                    needle_count++;
                    break;
                }
                hay = get_from_pos(haystack, next_pos);
                next_pos = next_pos_func(next_pos);
            }
        }
    return needle_count;
}

bool is_valid_for_cross_mas(char diagonal_char) {
    return diagonal_char == 'M' || diagonal_char == 'S';
}

gint64 cross_mas_search_2d(char* haystack) {
    gint64 cross_count = 0;
    Matrix matrix = new_matrix(haystack);
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            char hay = get_from_pos(matrix, pos);
            if (hay != 'A')
                continue;
            char up_right_char = get_from_pos(matrix, up_right(pos));
            if (!is_valid_for_cross_mas(up_right_char))
                continue;
            char up_left_char = get_from_pos(matrix, up_left(pos));
            if (!is_valid_for_cross_mas(up_left_char))
                continue;
            char down_right_char = get_from_pos(matrix, down_right(pos));
            if (!is_valid_for_cross_mas(down_right_char))
                continue;
            char down_left_char = get_from_pos(matrix, down_left(pos));
            if (!is_valid_for_cross_mas(down_left_char))
                continue;
            if (up_right_char == up_left_char && down_left_char == down_right_char && up_right_char != down_right_char)
                cross_count++;
            else if (up_right_char == down_right_char && up_left_char == down_left_char && up_left_char != up_right_char)
                cross_count++;
        }
    return cross_count;
}