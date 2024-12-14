#include "int_list.h"

void int_list_prepend(int_list** list, gint64 to_prepend) {
    *list = g_list_prepend(*list, GINT_TO_POINTER(to_prepend));
}

gint64 int_list_get(int_list* list) {
    return GPOINTER_TO_INT(list->data);
}

gint64 int_list_iter(int_list** list) {
    gint64 res = int_list_get(*list);
    *list = (*list)->next;
    return res;
}

gint64 int_list_index(int_list* list, gint64 index) {
    return GPOINTER_TO_INT(g_list_nth_data(list, index));
}

GList* int_list_parse(char* str) {
    int_list* list = NULL;
    while (*str) {
        if (*str >= '0' && *str <= '9')
            int_list_prepend(&list, strtoll(str, &str, decimal_base));
        str++;
    }
    list = g_list_reverse(list);
    return list;
}