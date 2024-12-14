#ifndef ADVENT_OF_CODE_2024_INT_LIST_H
#define ADVENT_OF_CODE_2024_INT_LIST_H

#include <glib.h>

#define decimal_base 10

typedef GList int_list;

void int_list_prepend(int_list** list, gint64 to_prepend);
gint64 int_list_get(int_list* list);
gint64 int_list_iter(int_list** list);
gint64 int_list_index(int_list* list, gint64 index);
GList* int_list_parse(char* str);

#endif //ADVENT_OF_CODE_2024_INT_LIST_H