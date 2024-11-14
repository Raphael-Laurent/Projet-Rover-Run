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
    t_localisation  location = randomLoc(map);
    int initial_cost = map.costs[location.pos.x][location.pos.y];
    int numberOfSons = sizeof(avails) / sizeof(avails[0]);
    t_node *root = createNode(initial_cost, numberOfSons, avails, 0, location);
    t_tree mytree = createNTree(root, 5, location, map);

    // Affichage de l'arbre
    //printf("Arbre n-aire:\n");
    printNTree(mytree);
    //parcoursNTree(mytree);
    int min_cost = INT_MAX;
    t_node *min_path = NULL;
    int path_length = 0;

    //findMinCostPath(root, 0, &min_cost, &min_path, &path_length);

    //printf("Smallest cost : (%d) :\n", min_cost);
    //printPath(min_path);
}

