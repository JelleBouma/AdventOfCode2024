#include "aoc25.h"

#define filled_char '#'
#define empty_char '.'

GList* keys = NULL;
GList* locks = NULL;

void setup(char* input) {
    char** keys_and_locks = split_on_empty_lines(input);
    while (*keys_and_locks) {
        Matrix* matrix = malloc(sizeof(Matrix));
        *matrix = new_matrix(*keys_and_locks);
        if (**keys_and_locks == filled_char)
            locks = g_list_prepend(locks, matrix);
        else
            keys = g_list_prepend(keys, matrix);
        keys_and_locks++;
    }
}

bool fits(Matrix key, Matrix lock) {
    Pos pos;
    for (pos.y = 1; pos.y < 6; pos.y++)
        for (pos.x = 0; pos.x < 5; pos.x++)
            if (get_from_pos(lock, pos) == filled_char && get_from_pos(key, pos) == filled_char)
                return false;
    return true;
}

gint64 get_fitting_key_lock_pairs() {
    gint64 res = 0;
    GList* key_iter = keys;
    while (key_iter) {
        Matrix* key = key_iter->data;
        GList* lock_iter = locks;
        while (lock_iter) {
            Matrix* lock = lock_iter->data;
            if (fits(*key, *lock))
                res++;
            lock_iter = lock_iter->next;
        }
        key_iter = key_iter->next;
    }
    return res;
}