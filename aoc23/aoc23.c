#include "aoc23.h"

GHashTable* connection_table;

void build_direct_connection_table(char *connections_str) {
    char** connections = split_lines(connections_str);
    while (*connections) {
        char* computer0 = *connections;
        computer0[2] = '\0';
        char* computer1 = computer0 + 3;
        GHashTable* computer0_connected = g_hash_table_lookup(connection_table, computer0);
        GHashTable* computer1_connected = g_hash_table_lookup(connection_table, computer1);
        if (!computer0_connected)
            computer0_connected = g_hash_table_new(g_str_hash, g_str_equal);
        if (!computer1_connected)
            computer1_connected = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(computer0_connected, computer1, NULL);
        g_hash_table_insert(computer1_connected, computer0, NULL);
        g_hash_table_insert(connection_table, computer0, computer0_connected);
        g_hash_table_insert(connection_table, computer1, computer1_connected);
        connections++;
    }
}

gint64 count_t_triangles(char* connections_str) {
    connection_table = g_hash_table_new(g_str_hash, g_str_equal);
    build_direct_connection_table(connections_str);
    GList* connected_computers = g_hash_table_get_keys(connection_table);
    gint64 res = 0;
    GList* connected_computers_iter = connected_computers;
    while (connected_computers_iter) {
        char* computer = connected_computers_iter->data;
        if (*computer == 't') {
            GHashTable* group = g_hash_table_lookup(connection_table, computer);
            if (group) {
                GList* connected0 = g_hash_table_get_keys(group);
                while (connected0) {
                    GList* connected1 = connected0->next;
                    GHashTable* connected0_table = g_hash_table_lookup(connection_table, connected0->data);
                    while (connected1) {
                        if (connected0_table && g_hash_table_contains(connected0_table,connected1->data))
                            res++;
                        connected1 = connected1->next;
                    }
                    g_hash_table_remove(connected0_table, computer);
                    connected0 = connected0->next;
                }
                g_list_free(connected0);
                g_hash_table_remove(connection_table, computer);
            }
        }
        connected_computers_iter = connected_computers_iter->next;
    }
    return res;
}