#include "n_tree.h"
#include <stdlib.h>
#include <stdio.h>

t_move* removeFromList(t_move* list, int val, int listLength) {
    int newLength = listLength - 1;
    if (newLength <= 0) return NULL;
    t_move* new_list = (t_move*)malloc(newLength * sizeof(t_move));
    if (new_list == NULL) {
        printf("Fail :/\n");
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < listLength; i++) {
        if (list[i] != val) {
            if (j < newLength) {
                new_list[j++] = list[i];
            } else {
                printf("Outside\n");
                break;
            }
        }
    }
    return new_list;
}


t_node* createNode(int val, int nd_sons, t_move* list_choix, int depth, t_localisation loc) {
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->ndSons = nd_sons;
    new_node->local = loc;
    if (nd_sons > 0) {
        new_node->sons = (t_node**)malloc(nd_sons * sizeof(t_node*));
    } else {
        new_node->sons = NULL;
    }
    t_move* new_avails = removeFromList(list_choix, val, nd_sons);
    new_node->avails = new_avails;
    new_node->depth = depth;
    return new_node;
}

t_tree createNTree(t_node* node, int size, t_localisation loc, t_map map) {
    if (node->depth < size) {
        for (int i = 0; i < node->ndSons; i++) {
            t_localisation new_loc = move(loc, node->avails[i]);

            int new_val = map.costs[new_loc.pos.x][new_loc.pos.y];
            t_move *new_avails = removeFromList(node->avails, node->avails[i], node->ndSons);

            t_node *new_son = createNode(new_val, node->ndSons - 1, new_avails, node->depth + 1, new_loc);
            node->sons[i] = new_son;

            createNTree(new_son, size, new_loc, map);
        }
    }
    t_tree tree;
    tree.root = node;
    return tree;
}


void printNTree(t_tree tree) {
    if (tree.root == NULL) return;

    printf("%d",tree.root->ndSons);

    // Indenter en fonction de la profondeur actuelle
    for (int i = 0; i < tree.root->depth; i++) {
        printf("    ");  // Ajoute 4 espaces pour chaque niveau de profondeur
    }

    // Afficher la loc et la value du nœud
    printf("loc : %d/%d//%s ; value : %d\n", tree.root->local.pos.x,tree.root->local.pos.y,tree.root->local.ori,tree.root->value);

    // Afficher récursivement chaque enfant avec une profondeur augmentée
    for (int i = 0; i < tree.root->ndSons; i++) {
        t_tree new_tree;
        new_tree.root = tree.root->sons[i];
        printNTree(new_tree);
    }
}

void parcoursNTree(t_tree tree) {
    t_node* temp;
    temp = tree.root;
    if (temp == NULL) {
        return;
    }
    printf("Value: %d ; Depth: %d \n", temp->value, temp->depth);
    for (int i = 0; i < temp->ndSons; i++) {
        if (temp->sons[i] != NULL) {
            t_tree child;
            child.root = temp->sons[i];
            parcoursNTree(child);
        }
    }
}

void findMinCostPath(t_node* node, int current_cost, int* min_cost, t_node** min_path, int* path_length) {
    if (node == NULL) return;
    current_cost += node->value;
    if (node->ndSons == 0) {
        if (current_cost < *min_cost) {
            *min_cost = current_cost;
            *min_path = node;
            *path_length = node->depth + 1;  // Update path length to include this node
        }
    }
    for (int i = 0; i < node->ndSons; i++) {
        findMinCostPath(node->sons[i], current_cost, min_cost, min_path, path_length);
    }
}

void printPath(t_node* node) {
    if (node == NULL) {
        printf("No path found >:c.\n");
        return;
    }
    printf("Cost: %d\n", node->value);
    if (node->ndSons == 0) {
        return;
    }
    for (int i = 0; i < node->ndSons; i++) {
        printPath(node->sons[i]);
    }
}

void deleteTree(t_tree* tree) {
    if (tree == NULL || tree->root == NULL) return;
    deleteNode(tree->root);
    free(tree);
}

void deleteNode(t_node *node) {
    if (node == NULL) return;
    for (int i = 0; i < node->ndSons; i++) {
        deleteNode(node->sons[i]);
    }
    free(node->sons);
    free(node->avails);
    free(node);
}
