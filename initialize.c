//
// Created by HugoW on 21/11/2024.
//

#include "initialize.h"
#include "stdlib.h"

t_map getRandomMap() {
    t_map map;
    char *listOfMapsWindows[] = {"..\\maps\\example1.map", "..\\maps\\example2.map","..\\maps\\bigmap.map"};
    char *listOfMapsNotWindows[] = {"../maps/example1.map", "../maps/example2.map","../maps/bigmap.map"};
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

void simulation() {
    t_map map = getRandomMap();
    int total_min_value = 0;
    int base_found = 0;
    int proba[7];
    t_localisation rover = loc_init(4, 3, NORTH);

    moveProbaInit(proba);
    printMapAndCost(&map);
    printf("\n");
    displayNewRoverLocation(map, rover.pos.x, rover.pos.y);

    while (total_min_value < 100 && !base_found) {
        t_tree mytree = getTree(&map, rover);
        t_node* min = minLocalisation(mytree.root, NULL, map);

        printf("\nGenerated Tree:\n");
        if (map.costs[min->local.pos.y][min->local.pos.x] == 0) {
            if (total_min_value == 0){
                total_min_value = min->value;
            }
            printf("\nBase found at (%d, %d) with a fuel usage of : %d !\n", min->local.pos.x, min->local.pos.y,total_min_value);
            base_found = 1;
        }
        else {
            total_min_value += min->value;
            printf("\nMoving rover to the next area (current sum of mins: %d):\n", total_min_value);
            rover = goToArea(min, map, rover);
            printf("\nRover's new position:\n");
            displayNewRoverLocation(map, rover.pos.x, rover.pos.y);
        }
    }
    if (total_min_value >= 100) {
        printf("\nStopping condition met: Total sum of mins >= 100\n");
    }
    if (base_found) {
        printf("\nStopping condition met: Base found\n");
    }
}

void NTreePrintExemple() {
    t_localisation rover = loc_init(4, 3, NORTH);
    t_map map = getRandomMap();
    t_move* avails = (t_move*)malloc(sizeof(t_move) * NB_RAND_MOVES);
    int move_proba[NONE];
    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    t_node* root = createNode(0, NB_RAND_MOVES, avails, 0, rover, NONE);
    t_tree exTree = createNTree(root, 3, rover, map);
    printNTree(exTree, map);
}