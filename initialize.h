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
 * @return none
*/
void printMapAndCost(t_map *map);


/**
 * @brief fonction pour créer l'arbre n-aire
 * @param *map : création de l'arbre en prenant en compte les coûts de la map
 * @param rover : position du rover
 * @return t_tree
*/
t_tree getTree(t_map *map, t_localisation rover);


/**
 * @brief fonction pour calculer le temp d'éxécution d'un programme
 * @return clock_t
*/
clock_t chronometerInit();


/**
 * @brief fonction pour arrêter le chronometre et avoir le temps
 * @param start : temps de début
 * @return double
*/
double chronometerEnd(clock_t start);


/**
 * @brief fonction pour initialiser les probabilités de chacuns des mouvements
 * @param proba[] : tableau de probabilités qui va être initialisé avec les valeurs de base des probabilités
 * @return none
*/
void moveProbaInit(int proba[]);

/**
 * @brief fonction pour choisir parmis les maps dans le fichier maps
 * @return t_map
*/
t_map getRandomMap();

#endif //ROVER_RUN_INITIALIZE_H
