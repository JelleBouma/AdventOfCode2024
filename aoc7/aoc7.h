#ifndef AOC7_H
#define AOC7_H

#include <glib.h>

#define equation_base 10

gint64 plus(gint64 a, gint64 b);
gint64 mul(gint64 a, gint64 b);
gint64 concat(gint64 a, gint64 b);

extern gint64(*plus_mul[2])(gint64, gint64);
extern gint64(*plus_mul_concat[3])(gint64, gint64);

gint64 get_total_calibration_result(char* input, gint64(**operators)(gint64, gint64), int operator_count);

gint64 get_calibration_result(char* line, gint64(**operators)(gint64, gint64), int operator_count);

#endif //AOC7_H