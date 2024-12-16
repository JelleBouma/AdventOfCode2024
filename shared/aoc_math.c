#include "aoc_math.h"

int count_digits_128(__int128 input) {
    int count = 0;
    while (input) {
        input /= 10;
        count++;
    }
    return count;
}

guint hash_128(gconstpointer v) {
    guint shifted = *(__int128*)v >> 64;
    return shifted ^ (guint)*(__int128*)v;
}

gboolean equal_128(gconstpointer v1, gconstpointer v2) {
    return *(__int128*)v1 == *(__int128*)v2;
}

char count_bits(char bits) {
    char count = 0;
    while (bits != 0) {
        if (bits % 2 == 1)
            count++;
        bits >>= 1;
    }
    return count;
}

gint64 gcd(gint64 a, gint64 b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

gint64 lcm(gint64 a, gint64 b) {
    return (a / gcd(a, b)) * b;
}
