//
// Created by HugoW on 28/10/2024.
//

#ifndef UNTITLED1_N_TREE_H
#define UNTITLED1_N_TREE_H
#include "loc.h"
#include "moves.h"
#include "map.h"


typedef struct s_node
{
    int value;//coût du déplacement
    int depth;//profondeur du noeud dans son arbre
    t_move move;
    struct s_node **sons; //tableau de pointeur
    int ndSons; //taille physique du tableau sons (et aussi avails)
    t_move *avails; //choix restants du noeud
    t_localisation local; // localisation du robot sur la map au "moment" du noeud
    struct s_node *parent;
}t_node;

t_node *createNode(int val, int nd_sons, t_move* list_choix, int depth, t_localisation loc, t_move mov);
void insertNode(t_node node);

void displayNode(t_node nodeToDisplay);

typedef struct n_tree {
    t_node* root;
} t_tree;


void deleteNode(t_node *node);

void deleteTree(t_tree *tree);

t_tree createNTree(t_node *node, int size, t_localisation loc, t_map map); //créé un arbre n-aire de déplacements à partir d'un t_node

t_move *removeFromList(t_move*, t_move, int);

void printNTree(t_tree tree, t_map map);

void parcoursNTree(t_tree tree); //parcours préfixe d'un arbre n-aire

void findMinCostPath(t_node* node, int current_cost, int* min_cost, t_node** min_path, int* path_length, t_node** current_path, t_move* current_moves, int depth);

void printPath(t_node*, t_map);

t_node *minLocalisation(t_node *current_node, t_node *min_node, t_map map);

void path(t_localisation, t_map, t_move*);

#endif //UNTITLED1_N_TREE_H
