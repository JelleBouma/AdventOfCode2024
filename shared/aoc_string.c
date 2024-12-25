#include "aoc_string.h"

char** split(char* str, char* separator) {
    return g_strsplit(str, separator, 0);
}

char** try_split(char* str, char** separators_to_try) {
    while (*separators_to_try) {
        if (strstr(str, *separators_to_try))
            return g_strsplit(str, *separators_to_try, 0);
        separators_to_try++;
    }
    return NULL;
}

char** split_lines(char* str) {
    char* new_lines[3] = { "\r\n", "\n", NULL };
    return try_split(str, new_lines);
}

char** split_on_empty_lines(char* str) {
    char* empty_lines[3] = { "\r\n\r\n", "\n\n", NULL };
    return try_split(str, empty_lines);
}

bool starts_with(char* str, char* prefix) {
    while (*prefix) {
        if (!*str || *prefix != *str)
            return false;
        prefix++;
        str++;
    }
    return true;
}

gint32 cmp_alphabetically(gconstpointer a, gconstpointer b) {
    char* str_a = (char*)a;
    char* str_b = (char*)b;
    while (*str_a && *str_b) {
        if (*str_a < *str_b)
            return -1;
        if (*str_a > *str_b)
            return 1;
        str_a++;
        str_b++;
    }
    return 0;
}