#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"

t_tree getTree(t_map *map);

void printMapAndCost(t_map *map);

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    srand(time(NULL));

    printMapAndCost(&map);


    // -----TEST------------------------------------------------------------------
    //map.costs = les coûts
    t_move tableau[9];
    int proba[7];
    proba[F_10] = 22;
    proba[F_20] = 15;
    proba[F_30] = 7;
    proba[B_10] = 7;
    proba[T_LEFT] = 21;
    proba[T_RIGHT] = 21;
    proba[U_TURN] = 7;

    for (int i = 0; i < 7; i++) {
        printf("%d ", proba[i]);
    }
    printf("\n");
    randomMoves(proba, tableau);
    printRndMvs(tableau);
    for (int i = 0; i < 7; i++) {
        printf("%d ", proba[i]);
    }
    printf("\n");

    t_tree mytree = getTree(&map);

    // Affichage de l'arbre
    printf("\nArbre n-aire:\n");
    printNTree(mytree);

    //Afficher le minimum de parcours
    //t_node *min = minLocalisation(mytree.root, min, map);
    //printf("%d\n",min->value);
    return 0;
}