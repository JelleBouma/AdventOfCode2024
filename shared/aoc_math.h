#ifndef ADVENTOFCODE2024_AOCMATH_H
#define ADVENTOFCODE2024_AOCMATH_H

#include "aoc_shared_imports.h"

#define decimal_base 10

int count_digits_128(__int128 input);

guint hash_128 (gconstpointer v);

gboolean equal_128 (gconstpointer v1, gconstpointer v2);

char count_bits(char bits);

#endif //ADVENTOFCODE2024_AOCMATH_H