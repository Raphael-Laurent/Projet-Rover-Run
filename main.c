#include <stdio.h>
#include "initialize.h"

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