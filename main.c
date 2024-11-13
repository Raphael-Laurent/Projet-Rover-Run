#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"


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

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    printf("\n");



    // -----TEST------------------------------------------------------------------
    //map.costs = les coûts
    t_move avails[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN};
    t_node *root = createNode(0,0, 5, avails, 0);
    t_tree mytree = createNTree(root, 5);

    // Affichage de l'arbre
    //printf("Arbre n-aire:\n");
    printNTree(mytree);


}
