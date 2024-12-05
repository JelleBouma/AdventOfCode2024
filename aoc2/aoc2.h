#ifndef AOC2_H
#define AOC2_H

#include <stdio.h>
#include <stdlib.h>

#define level_base 10
#define sector_max_byte_len 64

int is_safe(char* sector, int use_problem_dampener);
int count_safe_reports(FILE* file);

#endif //AOC2_H
