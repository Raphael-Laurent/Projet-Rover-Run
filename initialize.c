//
// Created by HugoW on 21/11/2024.
//

#include "initialize.h"


void printMapAndCost(t_map *map) {
    printf("Map created with dimensions %d x %d\n", (*map).y_max, (*map).x_max);
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            printf("%d ", (*map).soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            printf("%-5d ", (*map).costs[i][j]);
        }
        printf("\n");
    }
    displayMap((*map));
}

t_tree getTree(t_map *map) {
    t_localisation rover = loc_init(4,3, NORTH); //on initialise la position du rover
    t_move avails[NB_RAND_MOVES];
    int move_proba[NONE];
    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    t_node *root = createNode(0, 5, avails, 0, rover, NONE);
    t_tree mytree = createNTree(root, 3, rover, (*map));
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

clock_t chronometerInit() {
    return clock();
}

double chronometerEnd(clock_t start) {
    clock_t end = clock();
    double dt = ((double)(end - start)) / ((double)CLOCKS_PER_SEC);
    return dt;
}
