//
// Created by HugoW on 28/10/2024.
//
#include "n_tree.h"
#include <stdlib.h>

t_node *createNode(int val, int nd_sons) {
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));

    new_node->value = val;
    new_node->nbSons = nd_sons;
    new_node->sons = (t_node **)malloc(nd_sons*sizeof(t_node *));

    for(int i = 0; i < nd_sons; i++){
        new_node->sons[i]=NULL;
    }
    return new_node;
}

void insertNode(t_node nodeToAdd){

}
