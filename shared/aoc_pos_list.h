#ifndef ADVENT_OF_CODE_2024_POS_LIST_H
#define ADVENT_OF_CODE_2024_POS_LIST_H

#include "aoc_shared_imports.h"
#include "aoc_math.h"
#include "aoc_string.h"
#include "aoc_pos.h"

typedef GList PosList;

void pos_list_prepend(PosList** list, Pos to_prepend);
Pos pos_list_get(PosList* list);
Pos pos_list_iter(PosList** list);
Pos pos_list_index(PosList* list, gint64 index);

#endif //ADVENT_OF_CODE_2024_POS_LIST_H