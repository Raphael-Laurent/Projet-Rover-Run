//
// Created by HugoW on 28/10/2024.
//
#include "n_tree.h"
#include <stdlib.h>
#include <stdio.h>


t_move *removeFromList(t_move *list, t_move val, int len_list){
    /**
     * @brief enlève une valeur d'une liste, renvoie la liste sans la valeur
     * si la valeur n'est pas dans la liste, cela ne change rien
     * @param list : liste contenant toutes les valeurs
     * @param val : valeur que l'on veut retirer de la liste
     * @param len_list : longueur de la liste
     */
    if (len_list <= 0) {
        return list;
    }
    t_move *new_list = (t_move *)malloc((len_list - 1) * sizeof(t_move));
    if (new_list == NULL) {
        printf("Fail :c\n");
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < len_list; i++) {
        if (list[i] != val) {
            new_list[j++] = list[i];
        }
    }
    return new_list;
}


t_node *createNode(int val, int nd_sons, t_move* list_choix, int depth, t_localisation loc) {
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->ndSons = nd_sons;
    new_node->sons = (t_node **)malloc(nd_sons*sizeof(t_node *));
    new_node->avails = list_choix;
    new_node->depth = depth;
    new_node->local = loc;
    for(int i = 0; i < nd_sons; i++){
        new_node->sons[i]=NULL;
    }
    return new_node;
}


t_tree createNTree(t_node* node, int size, t_localisation loc, t_map map) {
    /**
     * @brief fonction récursive qui créée un arbre à partir du noeud racine
     * chaque nouveau étage de noeud possède une nouvelle liste avails qui correspond aux choix possibles
     * @param node : noeud
     * @param size : taille de l'arbre
     */
     if (node->depth < size) { // l'arbre est de taille 5 (5 mouvements par phase)
         int i;
         for (i = 0; i < node->ndSons; i++) {
             // nouvelle position utilisant le mouvement avails[i]
             t_localisation new_loc;
             new_loc = move(loc, node->avails[i]);
             //valeur de la case de la nouvelle position
             int new_val = map.costs[new_loc.pos.x][new_loc.pos.y];
             //on créé une nouvelle liste avails sans la valeur avails[i] pour le prochain fils
             t_move *new_avails;
             new_avails = removeFromList(node->avails, node->avails[i], node->ndSons);
             // on créé un nouveau fils du noeud
             t_node *new_son = createNode( new_val, node->ndSons - 1 , new_avails, node->depth + 1, new_loc);
             node->sons[i] = new_son;
             // et on appelle récursivement la fonction pour créer les fils des fils
             createNTree(new_son, size - 1, new_loc, map);
             free(new_avails);
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
    printf("loc : %d/%d//%s ; value : %d\n", tree.root->local.pos.x,tree.root->local.pos.y,getOriAsString(tree.root->local.ori),tree.root->value);
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

void findMinCostPath(t_node* node, int current_cost, int* min_cost, t_node** min_path, int* path_length, t_node** current_path, int depth) {
    if (node == NULL) return;

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
        findMinCostPath(node->sons[i], current_cost, min_cost, min_path, path_length, current_path, depth + 1);
    }
}

void printPath(t_node** path, int path_length) {
    if (path_length == 0) {
        printf("No path found.\n");
        return;
    }

    printf("Optimal path with minimum cost:\n");
    for (int i = 0; i < path_length; i++) {
        printf("Node %d -> ", path[i]->value);
    }
    printf("End\n");
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
