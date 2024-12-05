#include "aoc2.h"

int min(int a, int b) {
    return a < b ? a : b;
}

int are_levels_remaining(const char* str) {
    return str && *str && *str != '\r' && *str != '\n';
}

long is_bad_difference(long difference)
{
    long abs_difference = labs(difference);
    return abs_difference == 0 || abs_difference > 3;
}

int is_safe_impl(const long* levels, int level_count, int skip_index) {
    for (int ll = 1; ll < level_count; ll++) {
        if (ll == skip_index)
            continue;
        int prev_index = ll - 1 == skip_index ? ll - 2 : ll - 1;
        int prev_prev_index = ll - 1 == skip_index || ll - 2 == skip_index ? ll - 3 : ll - 2;
        if (prev_index < 0)
            continue;
        long difference = levels[ll] - levels[prev_index];
        long abs_difference = labs(difference);
        int bad_difference = abs_difference < 1 || abs_difference > 3;
        int inconsistent_order = prev_prev_index >= 0 && (levels[prev_index] - levels[prev_prev_index] > 0 != difference > 0);
        if (bad_difference || inconsistent_order)
            return 0;
    }
    return 1;
}

int is_safe(char* sector, int use_problem_dampener) {
    long levels[sector_max_byte_len / 2];
    int level_count = 0;
    while (are_levels_remaining(sector)) {
        levels[level_count] = strtol(sector, &sector, level_base);
        level_count++;
    }
    if (!use_problem_dampener)
        return is_safe_impl(levels, level_count, -1);
    for (int ll = 0; ll < level_count; ll++)
        if (is_safe_impl(levels, level_count, ll))
            return 1;
    return 0;
}

int count_safe_reports(FILE* file) {
    int safe_report_count = 0, safe_report_count_with_dampener = 0;
    char sector_string[sector_max_byte_len];
    while (fgets(sector_string, sector_max_byte_len, file)) {
        safe_report_count += is_safe(sector_string, 0);
        safe_report_count_with_dampener += is_safe(sector_string, 1);
    }
    printf("Safe reports (without problem dampener): %d\n", safe_report_count);
    printf("Safe reports (with problem dampener): %d\n", safe_report_count_with_dampener);
    return safe_report_count;
}