#ifndef ADVENTOFCODE2024_AOC_HASH_COUNTS_H
#define ADVENTOFCODE2024_AOC_HASH_COUNTS_H

#include "aoc_shared_imports.h"

typedef GHashTable HashCounts;

gint64 get_count(HashCounts* counts, gconstpointer key);
void hash_count_add(HashCounts* counts, gpointer key, gint64 to_add);
void hash_count_sub(HashCounts* counts, gpointer key, gint64 to_sub);

#endif //ADVENTOFCODE2024_AOC_HASH_COUNTS_H