#include "aoc22.h"

gint64 mix(gint64 secret, gint64 value) {
    return secret ^ value;
}

gint64 prune(gint64 secret) {
    return secret % 16777216;
}

gint64 get_next_secret_number(gint64 secret_number) {
    secret_number = prune(mix(secret_number, secret_number * 64));
    secret_number = prune(mix(secret_number, secret_number / 32));
    secret_number = prune(mix(secret_number, secret_number * 2048));
    return secret_number;
}

gint64 get_secret_number(gint64 secret_number, gint32 generations) {
    for (gint32 gg = 0; gg < generations; gg++)
        secret_number = get_next_secret_number(secret_number);
    return secret_number;
}

gint64 get_sum_of_secret_numbers(char* initial_nums_str, gint32 generations) {
    gint64 res = 0;
    Int64List* initial_numbers = int_list_parse(initial_nums_str);
    while(initial_numbers) {
        res += get_secret_number(int_list_get(initial_numbers), generations);
        initial_numbers = initial_numbers->next;
    }
    return res;
}