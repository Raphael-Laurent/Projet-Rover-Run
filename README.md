# Rover-Run-! 🚀
<sub>*Projet TI301 - Efrei semestre 3 (P2) || P2 2024-2025 || Projet en langage C* 
<br><br>

## Description :

Dans le cadre d'un projet semestriel lors de notre deuxième année de Programme Grande Ecole Ingénieurs à l'EFREI, nous avons réalisé une simulation de déplacement d'un rover. Ces déplacements tiennent compte de plusieurs facteurs comme le terrain et le fuel dépensé.  


## Fonctionnalités

Dans le cadre d'une mission sur Mars, nous devons aider un rover à atteindre sa base, avec une dépense de fuel minimum. 
Le coût d'un trajet est défini par le type de terrain que le rover traverse, et les mouvements qu'il peut effectuer sont décidés aléatoirement.    

Ainsi, nous avons dû créer un algorithme permettant au rover d'effectuer des "manches" où plusieurs chemins lui sont proposés selon les mouvements qui sont tirés au hasard.\n
Notre algorithme permet donc au robot de choisir soit un chemin qui dépense le moins de fuel, soit de choisir un chemin qui le mène directement à la base.  

Pour pouvoir calculer tous les chemins possibles, nous avons implémenté une structure d'arbre n-aire.  
Chaque feuille de l'arbre représente alors l'aboutissement d'un des chemins proposés au rover.  


## 📖 Description

*Rover-Run!* est un projet universitaire réalisé dans le cadre du module TI301. Le but est de concevoir et développer un programme en langage **C** simulant les déplacements d'un rover autonome sur une grille, en tenant compte de diverses contraintes (obstacles, énergie, itinéraires optimaux, etc.).


## 🛠️ Fonctionnalités

- Simulation du déplacement d'un rover autonome sur une grille 2D.
- Gestion des obstacles et du chemin optimal.
- Calcul de la consommation énergétique.
- Interface console interactive pour paramétrer la grille et suivre les déplacements.
- Fichiers de configuration pour personnaliser les scénarios.

