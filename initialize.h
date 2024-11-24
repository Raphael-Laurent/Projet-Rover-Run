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


/**
 * @brief fonction pour afficher la map ainsi que les coûts associés
 * @param *map : adresse de la map pour pouvoir l'afficher et afficher les coûts
*/
void printMapAndCost(t_map *map);


/**
 * @brief fonction pour créer l'arbre n-aire
 * @param *map : création de l'arbre en prenant en compte les coûts de la map
*/
t_tree getTree(t_map *map);


/**
 * @brief fonction pour calculer le temp d'éxécution d'un programme
*/
clock_t chronometerInit();


/**
 * @brief fonction pour arrêter le chronometre et avoir le temps
 * @param start : temps de début
*/
double chronometerEnd(clock_t start);


/**
 * @brief fonction pour initialiser les probabilités de chacuns des mouvements
 * @param proba[] : tableau de probabilités qui va être initialisé avec les valeurs
*/
void moveProbaInit(int proba[]);

#endif //ROVER_RUN_INITIALIZE_H
