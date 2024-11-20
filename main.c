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
    printf("%d", map.costs[2][2]);
    t_localisation new_loc, old_loc;
    old_loc.pos.x = 2;
    old_loc.pos.y = 2;
    old_loc.ori = NORTH;
    new_loc = move(old_loc, F_10);
    printf("%d",map.costs[new_loc.pos.y][new_loc.pos.x]);
    rover = loc_init(2,2, NORTH); //on initialise la position du rover
    t_move avails[7] = {F_10, F_20,B_10,F_30};
    t_node *root = createNode(map.costs[rover.pos.x][rover.pos.y], 4, avails, 0, rover, F_10);
    t_tree mytree = createNTree(root, 3, rover, map);

    // Affichage de l'arbre
    printf("Arbre n-aire:\n");
    printNTree(mytree);

    /*
    t_node *min;
    min = minLocalisation(mytree.root, min, map);
    printf("%d",min->value);*/


    /*
    int min_cost = INT_MAX;
    t_node* min_path = NULL;
    int path_length = 0;
    int *point = &path_length;
    t_node* current_path[10];  // Maximum depth
    t_move current_moves[10];  // Array to track moves at each step
    findMinCostPath(root, 0, &min_cost, &min_path, point, current_path, current_moves, 0);
    printf("Smallest cost: %d\n", min_cost);
    printPath(current_moves, path_length);*/
    return 0;

}
