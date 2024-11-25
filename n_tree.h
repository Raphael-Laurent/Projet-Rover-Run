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


/**
 * @brief fonction récursive qui créée un arbre à partir du noeud racine
 * chaque nouveau étage de noeud possède une nouvelle liste avails qui correspond aux choix possibles
 * @param val : valeur à insérer
 * @param nd_sons : nombre de fils à créer
 * @param list_choix : liste de choix de mouvements
 * @param depth : profondeur du noeud
 * @param loc : localisation du rover
 * @param mov : mouvement réalisé
*/
t_node *createNode(int val, int nd_sons, t_move* list_choix, int depth, t_localisation loc, t_move mov);

typedef struct n_tree {
    t_node* root;
} t_tree;


/**
 * @brief fonction pour libérer un noeud
 * @param *node : adresse du noeud pour libérer l'espace
*/
void deleteNode(t_node *node);


/**
 * @brief fonction pour libérer l'arbre à la fin
 * @param *tree : adresse de l'arbre pour pouvoir libérer l'espace
*/
void deleteTree(t_tree *tree);


/**
 * @brief fonction récursive qui créée un arbre à partir du noeud racine
 * chaque nouveau étage de noeud possède une nouvelle liste avails qui correspond aux choix possibles
 * @param node : noeud
 * @param size : taille de l'arbre
 * @param map : map des coûts
 */
t_tree createNTree(t_node *node, int size, t_localisation loc, t_map map); //créé un arbre n-aire de déplacements à partir d'un t_node


/**
 * @brief enlève une valeur d'une liste, renvoie la liste sans la valeur
 * si la valeur n'est pas dans la liste, cela ne change rien
 * @param list : liste contenant toutes les valeurs
 * @param val : valeur que l'on veut retirer de la liste
 * @param len_list : longueur de la liste
*/
t_move *removeFromList(t_move*, t_move, int);


/**
 * @brief fonction pour afficher l'ensemble de l'arbre n-aire dans la console
 * @param tree : arbre n-aire
*/
void printNTree(t_tree tree, t_map map);


/**
 * @brief fonction pour parcourir l'arbre n-aire
 * @param tree : arbre n-aire
*/
void parcoursNTree(t_tree tree); //parcours préfixe d'un arbre n-aire


/**
 * @brief fonction pour trouver le parcours avec le coût minimum dans l'arbre n-aire
 * @param *node : jsp encore
 * @param currenct_cost : coût actuel du parcour associé
 * @param *min_cost : adresse de la valeur minimum du parcours
 * @param **min_path : tableau pour stocker le parcour minimum
 * @param *path_length : adresse de la valeur de la longueur du chemin
 * @param **current_path : tableau pour stocker le chemin actuel
 * @param *current_moves : jsp
 * @param depth : profondeur actuelle du chemin
 *
*/
void findMinCostPath(t_node* node, int current_cost, int* min_cost, t_node** min_path, int* path_length, t_node** current_path, t_move* current_moves, int depth);

void printPath(t_node*, t_map);

void printPathSimple(t_node *feuille, t_map map);


/**
 * @brief fonction pour trouver le chemin avec le plus petit coût
 * @param *current_node : adresse du noeud actuel
 * @param *min_node : adresse du noeud avec la valeur minimum
 * @param map : map avec les coûts pour le parcours
*/
t_node *minLocalisation(t_node *current_node, t_node *min_node, t_map map);

void path(t_tree, t_map, t_move*);

#endif //UNTITLED1_N_TREE_H
