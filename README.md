# Rover-Run-!
Projet TI301 - Efrei semestre 3 (P2)
P2 2024-2025
Projet en langage C

---

Dans le cas d'une mission sur Mars, nous devons aider un rover à atteindre sa base, avec une dépense de fuel minimum.
Le coût d'un trajet est défini par le type de terrain que le rover traverse, et les mouvements qu'il peut effectuer sont décidés aléatoirement.


Ainsi, nous avons dû créer un algorithme permettant au rover d'effectuer des "manches" où plusieurs chemins lui sont proposés selon les mouvements qui sont tirés au hasard.\n
Notre algorithme permet donc au robot de choisir soit un chemin qui dépense le moins de fuel, soit de choisir un chemin qui le mène directement à la base.

Pour pouvoir calculer tous les chemins possibles, nous avons implémenté une structure d'arbre n-aire.
Chaque feuille de l'arbre représente alors l'aboutissement d'un des chemins proposés au rover.
