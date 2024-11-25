//
// Created by HugoW on 28/10/2024.
//
#include "n_tree.h"
#include <stdlib.h>
#include <stdio.h>


t_move *removeFromList(t_move *list, t_move val, int len_list) {
    if (len_list <= 0) {
        return list;
    }
    t_move *new_list = (t_move *) malloc((len_list - 1) * sizeof(t_move));
    if (new_list == NULL) {
        printf("Fail :c\n");
        return NULL;
    }
    int j = 0;
    int verif_suppression = 0;
    for (int i = 0; i < len_list; i++) {
        if (list[i] == val && !verif_suppression) {
            verif_suppression = 1;
        } else {
            new_list[j++] = list[i];
        }
    }
    return new_list;
}

t_node *createNode(int val, int nd_sons, t_move *list_choix, int depth, t_localisation loc, t_move mov) {
    t_node *new_node;
    new_node = (t_node *) malloc(sizeof(t_node));
    new_node->value = val;
    new_node->ndSons = nd_sons;
    new_node->sons = (t_node **) malloc(nd_sons * sizeof(t_node *));
    new_node->avails = list_choix;
    new_node->depth = depth;
    new_node->local = loc;
    new_node->move = mov;
    new_node->parent = NULL;
    for (int i = 0; i < nd_sons; i++) {
        new_node->sons[i] = NULL;
    }
    return new_node;
}


t_tree createNTree(t_node *node, int size, t_localisation loc, t_map map) {
    if ((map.costs[node->local.pos.y][node->local.pos.x] < 1000 &&
         map.costs[node->local.pos.y][node->local.pos.x] != 0) &&
        node->depth < size) {// l'arbre est de taille 5 (5 mouvements par phase)
        int i;
        for (i = 0; i < node->ndSons; i++) {

            // nouvelle position utilisant le mouvement avails[i]
            t_localisation new_loc;
            new_loc = move(loc, node->avails[i]);
            int new_val;
            if (isValidLocalisation(new_loc.pos, 6, 7)) {
                if (node->move == F_10 && node->value == 5 && node->parent->value == 0) {
                    printf("%s", getMoveAsString(node->avails[i]));
                }
                new_val = map.costs[new_loc.pos.y][new_loc.pos.x];

                t_move *new_avails;
                //on créé une nouvelle liste avails sans la valeur avails[i] pour le prochain fils
                new_avails = removeFromList(node->avails, node->avails[i], node->ndSons);

                // on créé un nouveau fils du noeud
                t_node *new_son = createNode(node->value + new_val, node->ndSons - 1, new_avails, node->depth + 1,
                                             new_loc,
                                             node->avails[i]);

                new_son->parent = node;
                node->sons[i] = new_son;

                // et on appelle récursivement la fonction pour créer les fils des fils
                createNTree(new_son, size, new_loc, map);

                free(new_avails);
            }
        }
        t_tree tree;
        tree.root = node;
        return tree;
    } else {
        node->ndSons = 0;
    }
}


void printNTree(t_tree tree, t_map map) {
    if (tree.root == NULL) { return; }
    // Indenter en fonction de la profondeur actuelle
    for (int i = 0; i < tree.root->depth; i++) {
        printf("    ");  // Ajoute 4 espaces pour chaque niveau de profondeur
    }
    // Afficher la loc et la value du nœud
    printf("loc : %d/%d//%s ; cost : %d ; value : %d ; direction : %s ", tree.root->local.pos.x,
           tree.root->local.pos.y,
           getOriAsString(tree.root->local.ori), map.costs[tree.root->local.pos.y][tree.root->local.pos.x],
           tree.root->value, getMoveAsString(tree.root->move));
    if (tree.root->parent != NULL) {
        printf("; value of the parent : %d ; depth : %d", tree.root->parent->value, tree.root->depth);
    }
    printf("\n");
    // Afficher récursivement chaque enfant avec une profondeur augmentée
    for (int i = 0; i < tree.root->ndSons; i++) {
        t_tree new_tree;
        new_tree.root = tree.root->sons[i];
        printNTree(new_tree, map);
    }
}

void parcoursNTree(t_tree tree) {
    t_node *temp;
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

void findMinCostPath(t_node *node, int current_cost, int *min_cost, t_node **min_path, int *path_length,
                     t_node **current_path, t_move *current_moves, int depth) {
    if (node == NULL) { return; }

    current_cost += node->value;
    current_path[depth] = node;

    if (node->ndSons == 0) {
        if (current_cost < *min_cost) {
            *min_cost = current_cost;
            *min_path = node;
            *path_length = depth + 1;
        }
    }

    for (int i = 0; i < node->ndSons; i++) {
        current_moves[depth] = node->avails[i];  // Record move leading to child
        findMinCostPath(node->sons[i], current_cost, min_cost, min_path, path_length, current_path, current_moves,
                        depth + 1);
    }
}


t_node *minLocalisation(t_node *current_node, t_node *min_node, t_map map) {
    if (current_node->ndSons == 0) {
        //printf("%d %d     \n",map.costs[current_node->local.pos.y][current_node->local.pos.x],map.costs[current_node->local.pos.y][current_node->local.pos.x]==0);
        if (min_node == NULL || map.costs[current_node->local.pos.y][current_node->local.pos.x] == 0) {
            min_node = current_node;
        } else if (map.costs[min_node->local.pos.y][min_node->local.pos.x] == 0) {
            return min_node;
        } else if (current_node->value < min_node->value) {
            min_node = current_node;
        }
    } else {
        for (int i = 0; i < current_node->ndSons; i++) {
            if (current_node->sons[i] != NULL) {
                min_node = minLocalisation(current_node->sons[i], min_node, map);
            }
        }
    }
    return min_node;
}

void path(t_tree tree, t_map map, t_move *avails) {
    // choisir le chemin le plus court et afficher le mouvement
    //printNTree(mytree, map);
    t_node *min = NULL;
    min = minLocalisation(tree.root, min, map);
    printPath(min, map);
    printPathSimple(min, map);

    //displayNewRoverLocation(map,min->local.pos.x,min->local.pos.y);
}

void printPath(t_node *feuille, t_map map) {
    if (feuille->parent != NULL) {
        printPath(feuille->parent, map);
    }
    printf("%s -->", getMoveAsString(feuille->move));
    if (feuille->move == NONE) {
        printf("Initialisation du rover :\n");
    } else if (map.costs[feuille->local.pos.y][feuille->local.pos.x] == 0) {
        printf("Vous avez atteint la base !\n");
    } else {
        printf("The robot does the movement : %s \n", getMoveAsString(feuille->move));
    }
    displayNewRoverLocation(map, feuille->local.pos.x, feuille->local.pos.y);
    printf("\n");
}

void printPathSimple(t_node *feuille, t_map map) {
    if (feuille->parent != NULL) {
        printPathSimple(feuille->parent, map);
    }
    printf("%s -->", getMoveAsString(feuille->move));
}


void deleteTree(t_tree *tree) {
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    deleteNode(tree->root);
    tree->root = NULL;
}

void deleteNode(t_node *node) {
    if (node == NULL) { return; }
    for (int i = 0; i < node->ndSons; i++) {
        deleteNode(node->sons[i]);
    }
    free(node->sons);
    free(node->avails);
    free(node);
}

