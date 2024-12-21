#ifndef ADVENTOFCODE2024_AOC_HASH_TREE_H
#define ADVENTOFCODE2024_AOC_HASH_TREE_H

#include "aoc_shared_imports.h"

typedef GHashTable HashTree;

typedef struct {
    gpointer value;
    HashTree* children;
} HashNode;

HashNode* hash_node_new(gpointer value);
void hash_tree_add_str(HashTree* tree, char* str);

#endif //ADVENTOFCODE2024_AOC_HASH_TREE_H
