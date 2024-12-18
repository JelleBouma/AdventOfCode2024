#include "aoc2.h"

gint64 is_bad_difference(gint64 difference)
{
    gint64 abs_difference = llabs(difference);
    return abs_difference == 0 || abs_difference > 3;
}

bool is_safe_impl(Int64List* levels, gint64 skip_index) {
    if (skip_index >= 0)
        levels = g_list_delete_link(levels, g_list_nth(levels, skip_index));
    while (levels->next) {
        levels = levels->next;
        gint64 difference = int_list_get(levels) - int_list_get(levels->prev);
        bool inconsistent_order = false;
        if (levels->prev->prev)
            inconsistent_order = int_list_get(levels->prev) - int_list_get(levels->prev->prev) > 0 != difference > 0;
        if (is_bad_difference(difference) || inconsistent_order)
            return false;
    }
    return true;
}

bool is_safe(Int64List* levels, bool use_problem_dampener) {
    gint64 level_count = g_list_length(levels);
    if (!use_problem_dampener)
        return is_safe_impl(levels, -1);
    for (int ll = 0; ll < level_count; ll++) {
        Int64List* levels_copy = g_list_copy(levels);
        Int64List* to_free = ll == 0 ? levels_copy->next : levels_copy;
        bool is_safe = is_safe_impl(levels_copy, ll);
        g_list_free(to_free);
        if (is_safe)
            return true;
    }
    return false;
}

gint64 count_safe_reports(char* input, bool use_problem_dampener) {
    gint64 safe_report_count = 0;
    GList* sectors = int_list_per_line(input);
    GList* sectors_iter = sectors;
    while (sectors_iter) {
        safe_report_count += is_safe(sectors_iter->data, use_problem_dampener);
        sectors_iter = sectors_iter->next;
    }
    return safe_report_count;
}