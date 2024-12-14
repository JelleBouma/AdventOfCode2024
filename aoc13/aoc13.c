#include "aoc13.h"

#define a_cost 3
#define b_cost 1

gint64 get_tokens_needed_to_win_or_zero(int_list** ints, gint64 goal_error) {
    double ax = (double)int_list_iter(ints);
    double ay = (double)int_list_iter(ints);
    double bx = (double)int_list_iter(ints);
    double by = (double)int_list_iter(ints);
    double x_goal = (double)(int_list_iter(ints) + goal_error);
    double y_goal = (double)(int_list_iter(ints) + goal_error);
    double b_xy_factor = by / bx;
    double ay_without_x = ay - (b_xy_factor * ax);
    gint64 a = round((y_goal - b_xy_factor * x_goal) / ay_without_x);
    double a_xy_factor = ay / ax;
    double by_without_x = by - (a_xy_factor * bx);
    gint64 b = round((y_goal - a_xy_factor * x_goal) / by_without_x);
    if ((gint64)ax * a + (gint64)bx * b == (gint64)x_goal && (gint64)ay * a + (gint64)by * b == (gint64)y_goal)
        return a * a_cost + b * b_cost;
    else
        return 0;
}

gint64 get_tokens_needed_to_win_all_possible(char* claw_machines, gint64 goal_error) {
    gint64 tokens_needed = 0;
    int_list* ints = int_list_parse(claw_machines);
    while (ints)
        tokens_needed += get_tokens_needed_to_win_or_zero(&ints, goal_error);
    return tokens_needed;
}