#include "aoc10.h"

int get_trailhead_score(Matrix matrix, Pos trailhead) {
    GHashTable* current_positions = g_hash_table_new(g_direct_hash, g_direct_equal);
    GHashTable* next_positions = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(current_positions, GINT_TO_POINTER(trailhead.as_int), NULL);
    for (char height = '1'; height <= '9'; height++) {
        GHashTableIter iter;
        g_hash_table_iter_init(&iter, current_positions);
        gpointer pos_elem;
        while (g_hash_table_iter_next(&iter, &pos_elem, NULL))
            for (int dd = 0; dd < 4; dd++) {
                Pos adjacent_pos = directions_4[dd]((Pos)GPOINTER_TO_INT(pos_elem));
                if (get_from_pos(matrix, adjacent_pos) == height)
                    g_hash_table_insert(next_positions, GINT_TO_POINTER(adjacent_pos.as_int), NULL);
            }
        g_hash_table_destroy(current_positions);
        current_positions = next_positions;
        next_positions = g_hash_table_new(g_direct_hash, g_direct_equal);
    }
    int trailhead_score = (int)g_hash_table_size(current_positions);
    g_hash_table_destroy(current_positions);
    return trailhead_score;
}

int get_trailhead_rating(Matrix matrix, Pos trailhead) {
    GList* current_positions = NULL;
    GList* next_positions = NULL;
    current_positions = g_list_prepend(current_positions, GINT_TO_POINTER(trailhead.as_int));
    for (char height = '1'; height <= '9'; height++) {
        while (current_positions) {
            for (int dd = 0; dd < 4; dd++) {
                Pos adjacent_pos = directions_4[dd]((Pos) GPOINTER_TO_INT(current_positions->data));
                if (get_from_pos(matrix, adjacent_pos) == height)
                    next_positions = g_list_prepend(next_positions, GINT_TO_POINTER(adjacent_pos.as_int));
            }
            current_positions = current_positions->next;
        }
        g_list_free(current_positions);
        current_positions = next_positions;
        next_positions = NULL;
    }
    int trailhead_score = (int)g_list_length(current_positions);
    g_list_free(current_positions);
    return trailhead_score;
}

long long get_total(char* map, int(*func)(Matrix, Pos)) {
    long long total = 0;
    Matrix matrix = new_matrix(map);
    Pos pos;
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            char height = get_from_pos(matrix, pos);
            if (height == '0')
                total += func(matrix, pos);
        }
    return total;
}

long long get_total_trailhead_score(char* map) {
    return get_total(map, get_trailhead_score);
}

long long get_total_trailhead_rating(char* map) {
    return get_total(map, get_trailhead_rating);
}