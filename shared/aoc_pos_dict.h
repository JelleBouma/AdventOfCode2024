#ifndef ADVENTOFCODE2024_AOC_POS_DICT_H
#define ADVENTOFCODE2024_AOC_POS_DICT_H

#include "aoc_shared_imports.h"
#include "aoc_pos.h"

typedef GHashTable PosCharDict;

PosCharDict* pos_char_dict_new();
bool pos_char_dict_insert(PosCharDict* dict, Pos pos, char character);
char pos_char_dict_lookup(PosCharDict* dict, Pos pos);
bool pos_char_dict_iter_next(GHashTableIter* iter, Pos* key, char* value);

#endif //ADVENTOFCODE2024_AOC_POS_DICT_H