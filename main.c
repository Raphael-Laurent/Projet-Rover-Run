#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"
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

    // -----TEST------------------------------------------------------------------
    //map.costs = les coûts

    t_localisation rover;
    rover = loc_init(3, 3, NORTH); //on initialise la position du rover
    t_move avails[7] = {F_10, F_20,B_10,T_RIGHT,U_TURN, F_30, T_LEFT};
    t_node *root = createNode(map.costs[rover.pos.x][rover.pos.y], 7, avails, 0, rover);
    t_tree mytree = createNTree(root, 7, rover, map);
    // Affichage de l'arbre
    printf("Arbre n-aire:\n");
    printNTree(mytree);
    //parcoursNTree(mytree);

    int min_cost = INT_MAX;
    t_node* min_path = NULL;
    int path_length = 0;
    t_node* current_path[10]; //profondeur max
    findMinCostPath(root, 0, &min_cost, &min_path, &path_length, current_path, 0);
    printf("Smallest cost: %d\n", min_cost);
    printPath(current_path, path_length);

    return 0;
}
