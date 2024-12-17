#include "aoc_pos_dict.h"

PosCharDict* pos_char_dict_new() {
    return g_hash_table_new(g_direct_hash, g_direct_equal);
}

bool pos_char_dict_insert(PosCharDict* dict, Pos pos, char character) {
    return g_hash_table_insert(dict, GINT_TO_POINTER(pos.as_int), GINT_TO_POINTER(character));
}

char pos_char_dict_lookup(PosCharDict* dict, Pos pos) {
    return GPOINTER_TO_INT(g_hash_table_lookup(dict, GINT_TO_POINTER(pos.as_int)));
}

bool pos_char_dict_iter_next(GHashTableIter* iter, Pos* key, char* value) {
    return g_hash_table_iter_next(iter, (gpointer*)key, (gpointer*)value);
}