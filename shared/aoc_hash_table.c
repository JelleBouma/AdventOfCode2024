#include "aoc_hash_table.h"

void hash_table_insert_table(GHashTable* base, GHashTable* to_insert) {
    if (to_insert) {
        GHashTableIter iter;
        g_hash_table_iter_init(&iter, to_insert);
        gpointer key, value;
        while (g_hash_table_iter_next(&iter, &key, &value))
            g_hash_table_insert(base, key, value);
    }
}