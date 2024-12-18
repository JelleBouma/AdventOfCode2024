#include "aoc_pos_list.h"

void pos_list_prepend(PosList** list, Pos to_prepend) {
    *list = g_list_prepend(*list, (gpointer)to_prepend.as_int);
}

Pos pos_list_get(PosList* list) {
    return (Pos)(gint64)list->data;
}

Pos pos_list_iter(PosList** list) {
    Pos res = pos_list_get(*list);
    *list = (*list)->next;
    return res;
}

Pos pos_list_index(PosList* list, gint64 index) {
    return (Pos)(gint64)g_list_nth_data(list, index);
}