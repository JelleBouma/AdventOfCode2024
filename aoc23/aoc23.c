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

void setup(char* connections_str) {
    connection_table = g_hash_table_new(g_str_hash, g_str_equal);
    build_direct_connection_table(connections_str);
}

gint64 count_t_triangles() {
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

GList* get_interconnected_groups() {
    GList* res = NULL;
    GList* connected_computers = g_hash_table_get_keys(connection_table);
    while (connected_computers) {
        char* computer = connected_computers->data;
        GList* connections = g_hash_table_get_keys(g_hash_table_lookup(connection_table, computer));
        while (connections) {
            char* connected_to = connections->data;
            GList* res_iter = res;
            while (res_iter) {
                bool is_interconnected = true;
                GList* interconnected_group = res_iter->data;
                while (interconnected_group) {
                    if (!g_hash_table_contains(g_hash_table_lookup(connection_table, interconnected_group->data), computer)) {
                        is_interconnected = false;
                        break;
                    }
                    interconnected_group = interconnected_group->next;
                }
                if (is_interconnected)
                    res_iter->data = g_list_prepend(res_iter->data, computer);
                res_iter = res_iter->next;
            }
            GList* new_interconnected_group = g_list_prepend(NULL, computer);
            new_interconnected_group = g_list_prepend(new_interconnected_group, connected_to);
            res = g_list_prepend(res, new_interconnected_group);
            connections = connections->next;
        }
        g_list_free(connections);
        connected_computers = connected_computers->next;
    }
    return res;
}

char* get_lan_party_password() {
    GList* interconnected_groups = get_interconnected_groups();
    gint64 largest_interconnect = 0;
    GList* password_list;
    while (interconnected_groups) {
        gint64 group_size = g_list_length(interconnected_groups->data);
        if (group_size > largest_interconnect) {
            largest_interconnect = group_size;
            password_list = interconnected_groups->data;
        }
        interconnected_groups = interconnected_groups->next;
    }
    password_list = g_list_sort(password_list, cmp_alphabetically);
    GString* res = g_string_new("");
    while (password_list) {
        g_string_append(res, password_list->data);
        if (password_list->next)
            g_string_append_c(res, ',');
        password_list = password_list->next;
    }
    return res->str;
}