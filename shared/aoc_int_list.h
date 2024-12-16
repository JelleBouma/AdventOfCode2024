#ifndef ADVENT_OF_CODE_2024_INT_LIST_H
#define ADVENT_OF_CODE_2024_INT_LIST_H

#include "aoc_shared_imports.h"
#include "aoc_math.h"
#include "aoc_string.h"

typedef GList IntList;

void int_list_prepend(IntList** list, gint64 to_prepend);
gint64 int_list_get(IntList* list);
gint64 int_list_iter(IntList** list);
gint64 int_list_index(IntList* list, gint64 index);
IntList* int_list_parse(char* str);
GList* int_list_per_line(char* str);

#endif //ADVENT_OF_CODE_2024_INT_LIST_H