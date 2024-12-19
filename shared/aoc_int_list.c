#include "aoc_int_list.h"

void int_list_prepend(Int64List** list, gint64 to_prepend) {
    *list = g_list_prepend(*list, (gpointer)to_prepend);
}

gint64 int_list_get(Int64List* list) {
    return (gint64)list->data;
}

gint64 int_list_iter(Int64List** list) {
    gint64 res = int_list_get(*list);
    *list = (*list)->next;
    return res;
}

gint64 int_list_index(Int64List* list, gint64 index) {
    return (gint64)g_list_nth_data(list, index);
}

Int64List* int_list_parse(char* str) {
    Int64List* list = NULL;
    while (*str) {
        if (*str == '-' || (*str >= '0' && *str <= '9'))
            int_list_prepend(&list, strtoll(str, &str, decimal_base));
        if (*str)
            str++;
    }
    list = g_list_reverse(list);
    return list;
}

GList* int_list_per_line(char* str) {
    GList* list_of_int_lists = NULL;
    char** lines = split_lines(str);
    char** line_iter = lines;
    while (*line_iter) {
        list_of_int_lists = g_list_prepend(list_of_int_lists, int_list_parse(*line_iter));
        line_iter++;
    }
    g_strfreev(lines);
    list_of_int_lists = g_list_reverse(list_of_int_lists);
    return list_of_int_lists;
}

gint64 int_list_take(Int64List** list) {
    gint64 taken = int_list_get(*list);
    *list = g_list_delete_link(*list, *list);
    return taken;
}

GString* int_list_to_string(Int64List* list) {
    GString* str = g_string_new("");
    while (list->next)
        g_string_append_printf(str, "%lld,", int_list_iter(&list));
    g_string_append_printf(str, "%lld", int_list_iter(&list));
    return str;
}

bool int_list_equal(Int64List* a, Int64List* b) {
    while (a && b)
        if (int_list_iter(&a) != int_list_iter(&b))
            return false;
    if (a != b)
        return false;
    return true;
}