//
// Created by HugoW on 28/10/2024.
//
#include "n_tree.h"
#include <stdlib.h>
#include <stdio.h>


t_move *removeFromList(t_move *list, int val, int len_list){
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
    for (i = 0; i <= len_list; i++) {
        if (val != list[i]) {
            new_list[j] = list[i];
            j++;
        }
    }
    return new_list;
}


t_node *createNode(int val, t_move mvt, int nd_sons, t_move* list_choix, int depth) {
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));

    new_node->value = val;
    new_node->id_mouvement = mvt;
    new_node->ndSons = nd_sons;
    new_node->sons = (t_node **)malloc(nd_sons*sizeof(t_node *));
    t_move *new_avails = removeFromList(list_choix, new_node->id_mouvement, nd_sons);//on enlève le mouvement du noeud actuel (son id_mouvement) à sa liste
    new_node->avails = new_avails; //tous les choix possibles qui dépend du noeud parent de ce nouveau noeud (si noeud = racine, initialisation du robot, liste complète)
    new_node->depth = depth;

    for(int i = 0; i < nd_sons; i++){
        new_node->sons[i]=NULL;
    }
    return new_node;
}


t_tree createNTree(t_node* node, int size) {
    /**
     * @brief fonction récursive qui créée un arbre à partir du noeud racine
     * chaque nouveau étage de noeud possède une nouvelle liste avails qui correspond aux choix possibles
     * @param node : noeud
     * @param size : taille de l'arbre
     * pour l'instant, les noeuds auront la valeur de l'id mouvement
     * créer à une depth plus grande que 3 fait cracher l'affichage :((
     */
     if (node->depth < size) { // l'arbre est de taille 5 (5 mouvements par phase)
         int i;
         for (i = 0; i < node->ndSons; i++) {

             // faire un case
             //static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};
             int cost;
             switch (node->avails[i]) {
                 case F_10 :
                     cost = 1;
                 case F_20 :
                     cost = 2;
                 case F_30 :
                     cost = 1;
                 case B_10 :
                     cost = 2;
                 case T_LEFT :
                     cost = 1;
                 case T_RIGHT :
                     cost = 2;
                 case U_TURN :
                     cost = 3;
                 default :
                     break;
             }

             int new_val = node->avails[i] + node->value;
             t_node *new_son = createNode( new_val, node->avails[i], node->ndSons - 1 , node->avails, node->depth + 1);
             node->sons[i] = new_son;
             createNTree(new_son, size - 1);
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

    // Afficher l'id_mouvement du nœud
    printf("Node ID: %s ; value : %d\n", _moves[tree.root->id_mouvement], tree.root->value);

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