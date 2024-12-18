#ifndef ADVENT_OF_CODE_2024_INT_LIST_H
#define ADVENT_OF_CODE_2024_INT_LIST_H

#include "aoc_shared_imports.h"
#include "aoc_math.h"
#include "aoc_string.h"

typedef GList Int64List;

void int_list_prepend(Int64List** list, gint64 to_prepend);
gint64 int_list_get(Int64List* list);
gint64 int_list_iter(Int64List** list);
gint64 int_list_index(Int64List* list, gint64 index);
Int64List* int_list_parse(char* str);
GList* int_list_per_line(char* str);
gint64 int_list_take(Int64List** list);
GString* int_list_to_string(Int64List* list);

#endif //ADVENT_OF_CODE_2024_INT_LIST_H