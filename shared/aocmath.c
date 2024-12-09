#include "aocmath.h"

int count_digits_128(__int128 input) {
    int count = 0;
    while (input) {
        input /= 10;
        count++;
    }
    return count;
}

guint hash_128 (gconstpointer v) {
    guint shifted = *(__int128*)v >> 64;
    return shifted ^ (guint)*(__int128*)v;
}

gboolean equal_128 (gconstpointer v1, gconstpointer v2) {
    return *(__int128*)v1 ==*(__int128*)v2;
}