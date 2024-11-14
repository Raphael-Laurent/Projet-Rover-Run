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
    int depth;//profondeur du noeud dans son arbre
    struct s_node **sons; //tableau de pointeur
    int ndSons; //taille physique du tableau
    t_move *avails; //choix restants du noeud
    t_localisation local; // localisation du robot sur la map au "moment" du noeud
}t_node;

t_node *createNode(int val, int nd_sons, t_move* list_choix, int depth, t_localisation loc);
void insertNode(t_node node);

void displayNode(t_node nodeToDisplay);

typedef struct n_tree {
    t_node* root;
} t_tree;

t_tree *createEmptyTree();
void deleteNode(t_node *node);
void deleteTree(t_tree *tree);
void displayTree(t_tree tree);

t_tree createNTree(t_node* node, int size, t_localisation loc, t_map map);//créer un arbre n-aire de déplacements à partir d'un t_node

t_move *removeFromList(t_move*, int val, int listLength);

void printNTree(t_tree tree);

void parcoursNTree(t_tree tree); //parcours préfixe d'un arbre n-aire

void findMinCostPath(t_node* node, int current_cost, int* min_cost, t_node** min_path, int* path_length);

void printPath(t_node* node);


#endif //UNTITLED1_N_TREE_H
