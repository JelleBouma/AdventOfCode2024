#include "aoc_hash_counts.h"

gint64 get_count(HashCounts* counts, gconstpointer key) {
    return (gint64)g_hash_table_lookup(counts, key);
}

void hash_count_add(HashCounts* counts, gpointer key, gint64 to_add) {
    g_hash_table_insert(counts, key, (gpointer)(get_count(counts, key) + to_add));
}

void hash_count_sub(HashCounts* counts, gpointer key, gint64 to_sub) {
    g_hash_table_insert(counts, key, (gpointer)(get_count(counts, key) - to_sub));
}