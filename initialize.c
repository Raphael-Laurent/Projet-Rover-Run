//
// Created by HugoW on 21/11/2024.
//

#include "initialize.h"


void printMapAndCost(t_map *map) {
    printf("Map created with dimensions %d x %d\n", (*map).y_max, (*map).x_max);
    for (int i = 0; i < (*map).y_max; i++)
    {
        for (int j = 0; j < (*map).x_max; j++)
        {
            printf("%d ", (*map).soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < (*map).y_max; i++)
    {
        for (int j = 0; j < (*map).x_max; j++)
        {
            printf("%-5d ", (*map).costs[i][j]);
        }
        printf("\n");
    }
    displayMap((*map));
}


t_tree getTree(t_map *map) {
    t_localisation rover;
    t_localisation new_loc, old_loc;
    old_loc.pos.x = 2;
    old_loc.pos.y = 2;
    old_loc.ori = NORTH;
    new_loc = move(old_loc, F_10);
    printf("Cout actuel %d", (*map).costs[new_loc.pos.y][new_loc.pos.x]);
    rover = loc_init(2,2, NORTH); //on initialise la position du rover
    t_move avails[7] = {F_10, F_20,B_10,F_30, U_TURN, T_RIGHT};
    t_node *root = createNode(0, 6, avails, 0, rover, NONE);
    t_tree mytree = createNTree(root, 5, rover, (*map));
    return mytree;
}

void moveProbaInit(int proba[]) {
    proba[F_10] = 22;
    proba[F_20] = 15;
    proba[F_30] = 7;
    proba[B_10] = 7;
    proba[T_LEFT] = 21;
    proba[T_RIGHT] = 21;
    proba[U_TURN] = 7;
}