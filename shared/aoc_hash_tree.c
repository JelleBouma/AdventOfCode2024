#include "aoc_hash_tree.h"

HashNode* hash_node_new(gpointer value) {
    HashNode* node = malloc(sizeof(HashNode));
    node->value = value;
    node->children = g_hash_table_new(g_direct_hash, g_direct_equal);
    return node;
}

void hash_tree_add_str(HashTree* tree, char* str) {
    gpointer char_key = (gpointer)(gint64)*str;
    bool is_last_char = *(str + 1) == '\0';
    HashNode* node;
    if (g_hash_table_contains(tree, char_key)) {
        node = g_hash_table_lookup(tree, char_key);
        if (is_last_char)
            node->value = (gpointer)true;
    }
    else {
        node = hash_node_new((gpointer)is_last_char);
        g_hash_table_insert(tree, char_key, node);
    }
    if (!is_last_char)
        hash_tree_add_str(node->children, str + 1);
}