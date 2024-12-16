#include "aoc3.h"

gint64 get_mul(GMatchInfo* match_info, int offset)
{
    char* first_number_str = g_match_info_fetch(match_info, offset);
    gint64 first_number = strtol(first_number_str, NULL, decimal_base);
    g_free(first_number_str);
    char* second_number_str = g_match_info_fetch(match_info, offset + 1);
    gint64 second_number = strtol(second_number_str, NULL, decimal_base);
    g_free(second_number_str);
    return first_number * second_number;
}

gint64 get_sum_of_muls(char* str)
{
    gint64 sum = 0;
    GMatchInfo* match_info;
    GRegex* regex = g_regex_new("mul\\((\\d+,(\\d+))\\)", 0, 0, NULL);
    g_regex_match (regex, str, 0, &match_info);
    while (g_match_info_matches (match_info))
    {
        sum += get_mul(match_info, 1);
        g_match_info_next (match_info, NULL);
    }
    g_match_info_free (match_info);
    g_regex_unref (regex);
    return sum;
}

gint64 get_sum_of_muls_with_dos_and_donts(char* str)
{
    bool mul_enabled = true;
    gint64 sum = 0;
    GMatchInfo* match_info;
    GRegex* regex = g_regex_new("(mul\\((\\d+),(\\d+)\\))|(do\\(\\))|(don't\\(\\))", 0, 0, NULL);
    g_regex_match (regex, str, 0, &match_info);
    while (g_match_info_matches (match_info))
    {
        char* mul_str = g_match_info_fetch(match_info, 1);
        if (mul_enabled && *mul_str)
        {
            sum += get_mul(match_info, 2);
        }
        else
        {
            char* do_str = g_match_info_fetch(match_info, 4);
            mul_enabled = *do_str;
            g_free(do_str);
        }
        g_free(mul_str);
        g_match_info_next (match_info, NULL);
    }
    g_match_info_free (match_info);
    g_regex_unref (regex);
    return sum;
}