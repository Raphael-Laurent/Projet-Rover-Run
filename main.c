#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"
#include "initialize.h"

void printTab(const int *tableau, int size);

int main() {
    t_map map = getRandomMap();

    printMapAndCost(&map);
    // -----TEST------------------------------------------------------------------
    //map.costs = les coûts

    printf("\n");

    int proba[7];
    moveProbaInit(proba);

    /*
    printTab(proba, 7); //Afficher les probabilités pour le debug
    randomMoves(proba, tableau);
    printRndMvs(tableau); //Afficher les moves pour le debug
    printTab(proba, 7); //Afficher les probabilités pour le debug
    */

    t_localisation rover = loc_init(4,3, NORTH); //on initialise la position du rover
    displayNewRoverLocation(map,rover.pos.x,rover.pos.y);

    t_tree mytree = getTree(&map, rover, ROVER);

    // Affichage de l'arbre
    printf("\nArbre n-aire:\n");
    printNTree(mytree, map);

    //Afficher le minimum de parcours
    t_node *min = minLocalisation(mytree.root, min, map);
    path(mytree, map);
    printf("%d\n",min->value);

    return 0;
}

void printTab(const int *tableau, int size) {
    for (int i = 0; i < size-1; i++) {
        printf("%d ", tableau[i]);
    }
    printf("%d \n", tableau[size-1]);
}

