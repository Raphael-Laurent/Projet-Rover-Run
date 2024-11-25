//
// Created by HugoW on 21/11/2024.
//

#ifndef ROVER_RUN_INITIALIZE_H
#define ROVER_RUN_INITIALIZE_H
#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"

void printMapAndCost(t_map *map);

t_tree getTree(t_map *map, t_localisation rover, t_soil id_case);

clock_t chronometerInit();

double chronometerEnd(clock_t start);

void moveProbaInit(int proba[]);

#endif //ROVER_RUN_INITIALIZE_H
