#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "initialize.h"

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

    while (total_min_value < 50 && !base_found) {
        t_tree mytree = getTree(&map, rover);

        printf("\nGenerated Tree:\n");
        //printNTree(mytree, map);

        t_node *min = minLocalisation(mytree.root, NULL, map);

        if (map.costs[min->local.pos.y][min->local.pos.x] == 0) {
            if (total_min_value == 0){
                total_min_value = min->value;
            }
            printf("\nBase found at (%d, %d) with a fuel usage of : %d !\n", min->local.pos.x, min->local.pos.y,total_min_value);
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