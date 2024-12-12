#include "aoc11.h"

void add_stone(GHashTable* stones, __int128* stone, __int128 count) {
    if (g_hash_table_contains(stones, stone)) {
        __int128* existing_count = g_hash_table_lookup(stones, stone);
        *existing_count += count;
        g_hash_table_insert(stones, stone, existing_count);
    }
    else {
        __int128* new_count = malloc(sizeof(__int128));
        *new_count = count;
        g_hash_table_insert(stones, stone, new_count);
    }
}

__int128 count_stones(GHashTable* stones) {
    __int128 total_stones = 0;
    GHashTableIter iter;
    g_hash_table_iter_init(&iter, stones);
    gpointer stone, stone_count;
    while (g_hash_table_iter_next(&iter, &stone, &stone_count)) {
        total_stones += *(__int128*)stone_count;
        free(stone);
        free(stone_count);
    }
    g_hash_table_destroy(stones);
    return total_stones;
}

GHashTable* parse_stones_from_string(const char *str) {
    GHashTable* stones = g_hash_table_new(hash_128, equal_128);
    while (*str) {
        __int128* new_stone = malloc(sizeof(__int128));
        *new_stone = strtoll(str, &str, stone_base);
        add_stone(stones, new_stone, 1);
    }
    return stones;
}

__int128 get_total_stones(const char *stones, int blinks) {
    GHashTable* current_stones = parse_stones_from_string(stones);
    for (int bb = 0; bb < blinks; bb++) {
        GHashTable* next_stones = g_hash_table_new(hash_128, equal_128);
        GHashTableIter iter;
        g_hash_table_iter_init(&iter, current_stones);
        __int128* stone_key;
        __int128* stone_count;
        while (g_hash_table_iter_next(&iter, (gpointer*)&stone_key, (gpointer*)&stone_count)) {
            if (!*stone_key) {
                *stone_key = 1;
                add_stone(next_stones, stone_key, *stone_count);
            }
            else if (count_digits_128(*stone_key) % 2 == 0) {
                int digit_count = count_digits_128(*stone_key);
                __int128 split = (__int128) pow(10, digit_count / 2);
                __int128* new_stone = malloc(sizeof(__int128));
                *new_stone = *stone_key % split;
                *stone_key /= split;
                add_stone(next_stones, new_stone, *stone_count);
                add_stone(next_stones, stone_key, *stone_count);
            } else {
                *stone_key *= 2024;
                add_stone(next_stones, stone_key, *stone_count);
            }
            free(stone_count);
        }
        g_hash_table_destroy(current_stones);
        current_stones = next_stones;
    }
    return count_stones(current_stones);
}