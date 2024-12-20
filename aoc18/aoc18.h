#ifndef AOC18_H
#define AOC18_H

#include <aoc_shared.h>

void one_time_setup(gint32 x_len, gint32 y_len);
gint32 get_minimum_steps_to_exit(char* input, gint64 input_limit);
char* get_first_blocking_byte(char* input);

#endif //AOC18_H