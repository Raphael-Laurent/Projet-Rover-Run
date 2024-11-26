//
// Created by HugoW on 21/11/2024.
//

#include "initialize.h"
#include "stdlib.h"

t_map getRandomMap() {
    t_map map;
    char *listOfMapsWindows[] = {"..\\maps\\example1.map", "..\\maps\\example2.map"};
    char *listOfMapsNotWindows[] = {"../maps/example1.map", "../maps/example2.map"};
    int sizeOfMap = sizeof(listOfMapsWindows) / sizeof(listOfMapsWindows[0]);
    srand(time(NULL));
    int mapNumber = rand() % sizeOfMap;
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile(listOfMapsWindows[mapNumber]);
#else
    map = createMapFromFile(listOfMapsNotWindows[mapNumber]);
#endif
    return map;
}

void printMapAndCost(t_map *map) {
    printf("Map created with dimensions %d x %d\n", (*map).y_max, (*map).x_max);
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            printf("%d ", (*map).soils[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            printf("%-5d ", (*map).costs[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    displayMap((*map));
}

t_tree getTree(t_map *map, t_localisation rover) {
    // rajouter taille arbre dans paramètres fonctions + localisation pour rover
    t_soil id_case = map->soils[rover.pos.y][rover.pos.x];
    t_move avails[NB_RAND_MOVES];
    int move_proba[NONE];
    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    for (int move = 0; move < NB_RAND_MOVES; move++) {
        printf("%s --> ", getMoveAsString(avails[move]));
    }
    printf("\n");
    int size;
    if (id_case == REG) {
        size = 4;
    } else {
        size = 5;
    }
    printf("size : %d\n", size);
    t_node *root = createNode(0, NB_RAND_MOVES, avails, 0, rover, NONE);
    t_tree mytree = createNTree(root, size, rover, (*map));
    path(mytree, *map);
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
    double dt = ((double) (end - start)) / ((double) CLOCKS_PER_SEC);
    return dt;
}
