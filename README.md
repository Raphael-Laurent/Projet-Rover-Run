# Rover-Run-! 🚀
<sub>*Projet TI301 - Efrei semestre 3 (P2) || P2 2024-2025 || Projet en langage C* 
<br><br>

## Description :
Ce repository a été créé dans le cadre de notre projet semestriel lors de notre deuxième année de Programme Grande Ecole Ingénieurs à l'EFREI. Nous avons dû réaliser **une simulation de déplacement d'un rover** sur Mars qui doit prendre en compte le terrain sur lequel il évolue et la quantité de fuel qu'il consomme afin de rejoindre sa base.  <br><br>
Le rover se déplace en phases, où une liste de mouvements sont tirés au sort à chaque fois.  
Comme choix de mouvements il a : **F_10** (avancer de 10m), **F_20** (avancer de 20m), **F_30** (avancer de 30m), **B_10** (reculer de 10m), **T_RIGHT** (tourner à droite), **T_LEFT** (tourner à gauche) et **U_TURN** (se retourner).  
Chaque mouvements possède 


## Fonctionnalités :
- Implémentation d'un arbre n-aire où chaque noeuds correspond à un mouvement potentiel fait par le rover.
- Calcul du chemin entre la feuille la plus petite d'un arbre n-aire et sa racine.
- Identification d'obstacles et applications des effets appropriés sur le rover.
- Tirage au hasard des mouvements et modification des probabilités
- Possibilité d'utiliser plusieurs maps sans problèmes
- Calcul du temps d'éxécution d'une fonction
- Vérification de l'arrivée à la base
- Modification de la position du rover en fin de phase

## 🛠️ Fonctionnalités

- Simulation du déplacement d'un rover autonome sur une grille 2D.
- Gestion des obstacles et du chemin optimal.
- Calcul de la consommation énergétique.
- Interface console interactive pour paramétrer la grille et suivre les déplacements.
- Fichiers de configuration pour personnaliser les scénarios.

## Utilisation :
Un code déjà inscrit dans le main.c permet 
