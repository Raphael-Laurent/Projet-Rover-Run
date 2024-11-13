#include "n_tree.h"
#include <stdlib.h>
#include <stdio.h>

t_move *removeFromList(t_move *list, int val, int listLength) {
    if (listLength <= 0) {
        return list;
    }
    int newLength = listLength;
    t_move *new_list = (t_move *)malloc(newLength * sizeof(t_move));
    if (new_list == NULL) {
        printf("Fail :c\n");
        return NULL;
    }
    for (int i = 0; i < listLength; i++) {
        new_list[i] = list[i];
    }
    return new_list;
}

t_node *createNode(int val, t_move mvt, int nd_sons, t_move* list_choix, int depth) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->id_mouvement = mvt;
    new_node->ndSons = nd_sons;
    if (nd_sons > 0) {
        new_node->sons = (t_node **)malloc(nd_sons * sizeof(t_node *));
    } else {
        new_node->sons = NULL;
    }
    t_move *new_avails = removeFromList(list_choix, mvt, nd_sons);
    new_node->avails = new_avails;
    new_node->depth = depth;
    for (int i = 0; i < nd_sons; i++) {
        new_node->sons[i] = NULL;
    }
    return new_node;
}

t_tree createNTree(t_node* node, int size) {
    if (node->depth < size) {
        for (int i = 0; i < node->ndSons; i++) {
            int cost = 0;
            switch (node->avails[i]) {
                case F_10:
                    cost = 1;
                    break;
                case F_20:
                    cost = 2;
                    break;
                case F_30:
                    cost = 1;
                    break;
                case B_10:
                    cost = 2;
                    break;
                case T_LEFT:
                    cost = 1;
                    break;
                case T_RIGHT:
                    cost = 2;
                    break;
                case U_TURN:
                    cost = 3;
                    break;
                default:
                    printf("nuh uh %d\n", node->avails[i]);
                    cost = 0; //si pas bon mouvement
                    break;
            }
            int new_val = node->value + cost;
            t_node *new_son = createNode(new_val, node->avails[i], node->ndSons, node->avails, node->depth + 1);
            node->sons[i] = new_son;
            createNTree(new_son, size);
        }
    }
    t_tree tree;
    tree.root = node;
    return tree;
}

void printNTree(t_tree tree) {
    if (tree.root == NULL){
        printf("Empty :O");
        return;
    }
    for (int i = 0; i < tree.root->depth; i++) {
        printf("    ");
    }
    char *move_str = getMoveAsString(tree.root->id_mouvement);
    printf("Val : %d ; Move : %s \n", tree.root->value,move_str);
    for (int i = 0; i < tree.root->ndSons; i++) { //Affichage récursif
        if (tree.root->sons[i] != NULL) {
            t_tree new_tree;
            new_tree.root = tree.root->sons[i];
            printNTree(new_tree);
        }
    }
}

void parcoursNTree(t_tree tree) {
    t_node* temp;
    temp = tree.root;
    if (temp == NULL) {
        return;
    }
    printf("Value: %d ; Depth: %d ; ID: %d\n", temp->value, temp->depth, temp->id_mouvement);
    for (int i = 0; i < temp->ndSons; i++) {
        if (temp->sons[i] != NULL) {
            t_tree child;
            child.root = temp->sons[i];
            parcoursNTree(child);
        }
    }
}

