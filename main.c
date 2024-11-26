#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "initialize.h"

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

    while (total_min_value < 50 && !base_found) {
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
    t_move avails[NB_RAND_MOVES];
    int move_proba[NONE];
    moveProbaInit(move_proba);
    randomMoves(move_proba, avails);
    t_node* root = createNode(0, NB_RAND_MOVES, avails, 0, rover, NONE);
    t_tree exTree = createNTree(root, 4, rover, map);
    printNTree(exTree, map);
}

int main() {
    // Interface
    int input;
    for (;;) {
        printf("Select an option, print an exemple NTree (1), start a simulation (2) or quit (3): ");
        scanf("%d", &input);
        switch (input) {
        case 1:
            NTreePrintExemple();
            break;
        case 2:
            simulation();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid input.\n");
        }
    }
}