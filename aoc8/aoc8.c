#include "aoc8.h"

GHashTable* find_antennas(Matrix matrix) {
    GHashTable* antenna_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    Pos pos = { .x = 0, .y = 0 };
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            char frequency = get_from_pos(matrix, pos);
            if (frequency == '.')
                continue;
            if (g_hash_table_contains(antenna_dict, GINT_TO_POINTER(frequency))) {
                GList* antennas = g_hash_table_lookup(antenna_dict, GINT_TO_POINTER(frequency));
                g_list_append(antennas, GINT_TO_POINTER(pos.as_int));
            }
            else
                g_hash_table_insert(antenna_dict, GINT_TO_POINTER(frequency), g_list_append(NULL, GINT_TO_POINTER(pos.as_int)));
        }
    return antenna_dict;
}

void insert_antinodes(GHashTable* antinodes, Pos antenna_0, Pos antenna_1, Matrix matrix) {
    Pos difference = minus(antenna_0, antenna_1);
    Pos antinode_0 = minus(antenna_0, mul(difference, new_pos(2, 2)));
    Pos antinode_1 = plus(antenna_1, mul(difference, new_pos(2, 2)));
    if (is_in_range(antinode_0, matrix))
        g_hash_table_insert(antinodes, GINT_TO_POINTER(antinode_0.as_int), NULL);
    if (is_in_range(antinode_1, matrix))
        g_hash_table_insert(antinodes, GINT_TO_POINTER(antinode_1.as_int), NULL);
}

void insert_resonant_antinodes(GHashTable* antinodes, Pos antinode_0, Pos antinode_1, Matrix matrix) {
    Pos difference = minus(antinode_0, antinode_1);
    while (is_in_range(antinode_0, matrix)) {
        g_hash_table_insert(antinodes, GINT_TO_POINTER(antinode_0.as_int), NULL);
        antinode_0 = minus(antinode_0, difference);
    }
    while (is_in_range(antinode_1, matrix)) {
        g_hash_table_insert(antinodes, GINT_TO_POINTER(antinode_1.as_int), NULL);
        antinode_1 = plus(antinode_1, difference);
    }
}

long get_antinode_location_count(char* city, bool are_resonant) {
    GHashTable* antinode_locations = g_hash_table_new(g_direct_hash, g_direct_equal);
    Matrix matrix = new_matrix(city);
    GHashTable* antennas = find_antennas(matrix);
    GHashTableIter iter;
    gpointer frequency, antennas_for_frequency;
    g_hash_table_iter_init (&iter, antennas);
    while (g_hash_table_iter_next(&iter, &frequency, &antennas_for_frequency))
    {
        int antenna_count = (int)g_list_length(antennas_for_frequency);
        for (int aa0 = 0; aa0 < antenna_count; aa0++)
            for (int aa1 = aa0 + 1; aa1 < antenna_count; aa1++) {
                Pos antenna_0 = (Pos)GPOINTER_TO_INT(g_list_nth_data(antennas_for_frequency, aa0));
                Pos antenna_1 = (Pos)GPOINTER_TO_INT(g_list_nth_data(antennas_for_frequency, aa1));
                if (are_resonant)
                    insert_resonant_antinodes(antinode_locations, antenna_0, antenna_1, matrix);
                else
                    insert_antinodes(antinode_locations, antenna_0, antenna_1, matrix);
            }
    }
    return (long)g_hash_table_size(antinode_locations);
}