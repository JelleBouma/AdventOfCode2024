#ifndef AOC7_H
#define AOC7_H

#include <glib.h>

#define equation_base 10

long long plus(long long a, long long b);
long long mul(long long a, long long b);
long long concat(long long a, long long b);

extern long long(*plus_mul[2])(long long, long long);
extern long long(*plus_mul_concat[3])(long long, long long);

long long get_total_calibration_result(char* input, long long(**operators)(long long, long long), int operator_count);

long long get_calibration_result(char* line, long long(**operators)(long long, long long), int operator_count);

#endif //AOC7_H