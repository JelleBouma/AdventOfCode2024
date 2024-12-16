#include "aoc1.h"

int cmpll(const void* a, const void* b) {
    if (*(gint64*)a - *(gint64*)b < 0)
        return -1;
    if (*(gint64*)a - *(gint64*)b > 0)
        return 1;
    return 0;
}

int count_ids(char *str) {
    char* next_id = str;
    int count = 0;
    while (next_id && *next_id) {
        strtol(next_id, &next_id, decimal_base);
        count++;
    }
    return count;
}

void fill_sorted_columns(char* input, gint64** columns, gint64 pair_count) {
    char* next_location_id = input;
    for (int pp = 0; pp < pair_count; pp++) {
        columns[0][pp] = strtol(next_location_id, &next_location_id, decimal_base);
        columns[1][pp] = strtol(next_location_id, &next_location_id, decimal_base);
    }
    qsort(columns[0], pair_count, sizeof(gint64), cmpll);
    qsort(columns[1], pair_count, sizeof(gint64), cmpll);
}

gint64 get_total_distance(char* input) {
    gint64 id_count = count_ids(input);
    gint64 pair_count = id_count / 2;
    gint64 column_0[pair_count], column_1[pair_count];
    gint64* columns[2] = { column_0, column_1 };
    fill_sorted_columns(input, columns, pair_count);
    gint64 total_distance = 0;
    for (int pp = 0; pp < pair_count; pp++)
        total_distance += llabs(columns[0][pp] - columns[1][pp]);
    return total_distance;
}

gint64 get_similarity_score(char* input) {
    gint64 id_count = count_ids(input);
    gint64 pair_count = id_count / 2;
    gint64 column_0[pair_count], column_1[pair_count];
    gint64* columns[2] = { column_0, column_1 };
    fill_sorted_columns(input, columns, pair_count);
    gint64 similarity_score = 0;
    int indexer_0 = 0, indexer_1 = 0;
    while (indexer_0 < pair_count && indexer_1 < pair_count)
    {
        const gint64 element_0 = columns[0][indexer_0];
        const gint64 element_1 = columns[1][indexer_1];
        if (element_0 == element_1)
        {
            indexer_0++;
            indexer_1++;
            int count_0 = 1;
            int count_1 = 1;
            while (element_0 == columns[0][indexer_0] && indexer_0 < pair_count)
            {
                count_0++;
                indexer_0++;
            }
            while (element_1 == columns[1][indexer_1] && indexer_1 < pair_count)
            {
                count_1++;
                indexer_1++;
            }
            similarity_score += count_0 * count_1 * element_0;
        }
        else if (element_0 < element_1)
            indexer_0++;
        else if (element_0 > element_1)
            indexer_1++;
    }
    return similarity_score;
}