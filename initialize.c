//
// Created by HugoW on 21/11/2024.
//

#include "initialize.h"
#include "stdlib.h"

t_map getRandomMap() {
    t_map map;
    char *listOfMapsWindows[] = {"..\\maps\\example1.map","..\\maps\\example2.map"};
    char *listOfMapsNotWindows[] = {"../maps/example1.map","../maps/example2.map"};
    srand(time(NULL));    int mapNumber = rand() % 2;
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
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            printf("%-5d ", (*map).costs[i][j]);
        }
        printf("\n");
    }
    displayMap((*map));
}

t_tree getTree(t_map *map, t_localisation rover, t_soil id_case) {
    // rajouter taille arbre dans paramètres fonctions + localisation pour rover
    t_move avails[NB_RAND_MOVES];
    int move_proba[NONE];
    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    t_node *root = createNode(0, 5, avails, 0, rover, NONE);
    t_tree mytree = createNTree(root, 3, rover, (*map));
    return mytree;
}

//void path( t_map map, t_move *avails){
//    // partir d'une localisation pour générer un arbre n-aire, choisir le chemin le plus court et afficher le mouvement
//    t_node *root = createNode(0, 7, avails, 0, rover, NONE);
//    t_tree mytree = createNTree(root, 5, rover, map);
//    //printNTree(mytree, map);
//    t_node *min = NULL;
//    min = minLocalisation(mytree.root, min, map);
//    printPath(min, map);
//    printPathSimple(min,map);
//
//    //displayNewRoverLocation(map,min->local.pos.x,min->local.pos.y);
//}

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
