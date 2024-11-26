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
         map.costs[node->local.pos.y][node->local.pos.x] != 0) && node->depth < size) {
        int i;
        for (i = 0; i < node->ndSons; i++) {

            // nouvelle position utilisant le mouvement avails[i]
            t_localisation new_loc;
            t_move move_id = node->avails[i];
            if (map.soils[node->local.pos.y][node->local.pos.x] == 2) {
                move_id = updateERGMovement(node->avails[i]);
                node->avails[i] = move_id;
            }
            new_loc = move(loc, move_id);

            int new_val;
            if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
                new_val = map.costs[new_loc.pos.y][new_loc.pos.x];

                t_move *new_avails;
                //on créé une nouvelle liste avails sans la valeur avails[i] pour le prochain fils
                new_avails = removeFromList(node->avails, node->avails[i], node->ndSons);

                // on créé un nouveau fils du noeud
                t_node *new_son = createNode(node->value + new_val, node->ndSons - 1, new_avails, node->depth + 1,new_loc,move_id);

                if(node->avails[i] == T_LEFT || node->avails[i] == T_RIGHT || node->avails[i] == U_TURN) {
                    new_son->value = node->value;
                }

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
    printf("loc : %d/%d//%s ; cost : %d ; value : %d ; Move : %s ", tree.root->local.pos.x, tree.root->local.pos.y,
           getOriAsString(tree.root->local.ori), map.costs[tree.root->local.pos.y][tree.root->local.pos.x], tree.root->value, getMoveAsString(tree.root->move));
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


t_node *minLocalisation(t_node *current_node, t_node *min_node, t_map map) {
    if (current_node->ndSons == 0) {
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

void path(t_tree tree, t_map map) {
    t_node *min = NULL;
    min = minLocalisation(tree.root, min, map);
    printPath(min, map);
    printPathSimple(min, map);
}

t_localisation goToArea(t_node *feuille, t_map map, t_localisation rover) {
    if (feuille == NULL) {
        return rover;
    }
    if (feuille->parent != NULL) {
        rover = goToArea(feuille->parent, map, rover);
    }
    rover = move(rover, feuille->move); //I like to move it move it
    printf("The rover moves: %s\n", getMoveAsString(feuille->move));
    return rover;
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
    printf("%d", feuille->value);
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