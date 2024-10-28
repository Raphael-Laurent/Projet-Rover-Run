//
// Created by HugoW on 28/10/2024.
//

#ifndef UNTITLED1_N_TREE_H
#define UNTITLED1_N_TREE_H



typedef struct s_node
{
    int value;
    int depth;
    struct s_node **sons; //tableau de pointeur
    int nbSons; //taille physique du tableau
}t_node;

t_node *createNode(int val, int nd_sons);
void insertNode(t_node nodeToAdd);
void deleteNode(t_node nodeToDelete);
void displayNode(t_node nodeToDisplay);

typedef struct n_tree {
    t_node* root;
} t_tree;

t_tree *createEmptyTree();
void deleteTree();
void displayTree(t_tree tree);









#endif //UNTITLED1_N_TREE_H
