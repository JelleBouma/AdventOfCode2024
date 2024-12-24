#include "aoc22.h"

#define generations 2000

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

gint64 get_secret_number(gint64 secret_number) {
    for (gint32 gg = 0; gg < generations; gg++)
        secret_number = get_next_secret_number(secret_number);
    return secret_number;
}

gint64 get_sum_of_secret_numbers(char* initial_nums_str) {
    gint64 res = 0;
    Int64List* initial_numbers = int_list_parse(initial_nums_str);
    while (initial_numbers) {
        res += get_secret_number(int_list_get(initial_numbers));
        initial_numbers = initial_numbers->next;
    }
    return res;
}

HashCounts* get_buy_table(gint64 secret_number) {
    HashCounts* res = g_hash_table_new(g_direct_hash, g_direct_equal);
    gint64 key = 0;
    for (gint32 gg = 0; gg < generations; gg++) {
        gint64 old_price = secret_number % 10;
        secret_number = get_next_secret_number(secret_number);
        gint64 new_price = secret_number % 10;
        gint64 diff = new_price - old_price;
        key <<= 8;
        key &= 0xFFFFFFFF;
        key += diff + 10;
        if (gg > 3 && !g_hash_table_contains(res, (gpointer)key))
            hash_count_add(res, (gpointer)key, new_price);
    }
    return res;
}

gint64 get_highest_total_price(char* initial_nums_str) {
    gint64 res = 0;
    Int64List* initial_numbers = int_list_parse(initial_nums_str);
    GList* tables = NULL;
    while (initial_numbers) {
        tables = g_list_prepend(tables, get_buy_table(int_list_get(initial_numbers)));
        initial_numbers = initial_numbers->next;
    }
    HashCounts* totals = g_hash_table_new(g_direct_hash, g_direct_equal);
    while (tables) {
        GHashTableIter iter;
        g_hash_table_iter_init(&iter, tables->data);
        gpointer key;
        gint64 price;
        while (g_hash_table_iter_next(&iter, &key, (gpointer*)&price))
            hash_count_add(totals, key, price);
        tables = tables->next;
    }
    GHashTableIter iter;
    g_hash_table_iter_init(&iter, totals);
    gint64 total_price;
    while (g_hash_table_iter_next(&iter, NULL, (gpointer*)&total_price))
        if (total_price > res)
            res = total_price;
    return res;
}