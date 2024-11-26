#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"
#include "initialize.h"

void printTab(const int *tableau, int size);

int main() {
    t_map map = getRandomMap();

    printMapAndCost(&map);

    printf("\n");

    int proba[7];
    moveProbaInit(proba);

    t_localisation rover = loc_init(4, 3, NORTH);
    displayNewRoverLocation(map, rover.pos.x, rover.pos.y);

    int total_min_value = 0;
    int base_found = 0;

    while (total_min_value < 100 && !base_found) {
        t_tree mytree = getTree(&map, rover);

        printf("\nGenerated Tree:\n");
        printNTree(mytree, map);

        t_node *min = minLocalisation(mytree.root, NULL, map);

        if (map.costs[min->local.pos.y][min->local.pos.x] == 0) {
            printf("\nBase found at (%d, %d)!\n", min->local.pos.x, min->local.pos.y);
            base_found = 1;
        } else {
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

    return 0;
}


void printTab(const int *tableau, int size) {
    for (int i = 0; i < size-1; i++) {
        printf("%d ", tableau[i]);
    }
    printf("%d \n", tableau[size-1]);
}

