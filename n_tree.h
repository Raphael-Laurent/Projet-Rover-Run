//
// Created by H on 28/10/2024.
//

#ifndef UNTITLED1_N_TREE_H
#define UNTITLED1_N_TREE_H
#include "loc.h"
#include "moves.h"


typedef struct s_node
{
    int value;//coût du déplacement
    t_move id_mouvement;//identifiant du déplacement
    int depth;//profondeur du noeud dans son arbre
    struct s_node **sons; //tableau de pointeur
    int ndSons; //taille physique du tableau
    t_move *avails; //choix restants du noeud
}t_node;

t_node *createNode(int val, t_move mvt, int nd_sons, t_move* list_choix, int depth);
void insertNode(t_node node);
void deleteNode(t_node nodeToDelete);
void displayNode(t_node nodeToDisplay);

typedef struct n_tree {
    t_node* root;
} t_tree;

t_tree *createEmptyTree();
void deleteTree();
void displayTree(t_tree tree);

t_tree createNTree(t_node *node, int size); //créer un arbre n-aire de déplacements à partir d'un t_node

t_move *removeFromList(t_move*, int val, int listLength);

void printNTree(t_tree tree);

void parcoursNTree(t_tree tree); //parcours préfixe d'un arbre n-aire






#endif //UNTITLED1_N_TREE_H
