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
    t_move* new_list = (t_move*)malloc(sizeof(t_move)*(len_list - 1));
    int i, j;
    j = 0;
    for (i = 0; i < len_list; i++) {
        if (val != list[i]) {
            new_list[j] = list[i];
            j++;
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

             //static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};
             // nouvelle position utilisant le mouvement avails[i]
             t_localisation new_loc;
             new_loc = move(loc, node->avails[i]);
             printf("%d %d  -  ", new_loc.pos.x, new_loc.pos.y);

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
         }
         printf("stop\n");
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

void parcoursNTree(t_tree tree){
    /**
     * @brief : parcours préfixe d'un arbre
     * @param tree : arbre n-aire
     */
     t_node* temp;
     temp = tree.root;

}