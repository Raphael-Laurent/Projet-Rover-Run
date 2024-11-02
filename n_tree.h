//
// Created by HugoW on 28/10/2024.
//

#ifndef UNTITLED1_N_TREE_H
#define UNTITLED1_N_TREE_H



typedef struct s_node
{
    int value;
    int id_mouvement;
    int depth;
    struct s_node **sons; //tableau de pointeur
    int ndSons; //taille physique du tableau
    int *avails; //choix restants du noeud
}t_node;

t_node *createNode(int val, int mvt, int nd_sons, int* list_choix, int depth);
void insertNode(t_node node);
void deleteNode(t_node nodeToDelete);
void displayNode(t_node nodeToDisplay);

typedef struct n_tree {
    t_node* root;
} t_tree;

t_tree *createEmptyTree();
void deleteTree();
void displayTree(t_tree tree);

t_tree createNTree(t_node *node); //créé un arbre n-aire de déplacements à partir d'un t_node

int *removeFromList(int*, int, int);

void printNTree(t_tree tree);






#endif //UNTITLED1_N_TREE_H
