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
    t_move avails[NB_RAND_MOVES];
    int move_proba[NONE];

    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    old_loc.pos.x = 2;
    old_loc.pos.y = 2;
    old_loc.ori = NORTH;
    new_loc = move(old_loc, F_10);
    printf("Cout actuel %d", (*map).costs[new_loc.pos.y][new_loc.pos.x]);
    rover = loc_init(2,2, NORTH); //on initialise la position du rover
    
    t_node *root = createNode(0, 6, avails, 0, rover, NONE);
    t_tree mytree = createNTree(root, 5, rover, (*map));
    return mytree;
}

clock_t chronometerInit() {
    return clock();
}

double chronometerEnd(clock_t start) {
    clock_t end = clock();
    double dt = ((double)(end - start)) / ((double)CLOCKS_PER_SEC);
    return dt;
}
