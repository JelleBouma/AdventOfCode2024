#ifndef AOC2_H
#define AOC2_H

#include <aoc_shared.h>

bool is_safe(Int64List* sector, bool use_problem_dampener);
gint64 count_safe_reports(char* input, bool use_problem_dampener);

#endif //AOC2_H