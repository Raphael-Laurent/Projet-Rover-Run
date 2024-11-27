# Rover-Run-! 🚀
<sub>*Projet TI301 - Efrei semestre 3 (P2) || P2 2024-2025 || Projet en langage C* 
<br><br>

**Lien Github :** https://github.com/Raphael-Laurent/Projet-Rover-Run.git

## Description :
Ce repository a été créé dans le cadre de notre projet semestriel lors de notre deuxième année de Programme Grande Ecole Ingénieurs à l'EFREI. Nous avons dû réaliser **une simulation de déplacement d'un rover** sur Mars qui doit prendre en compte le terrain sur lequel il évolue et la quantité de fuel qu'il consomme afin de rejoindre sa base.  <br><br>

Le rover se déplace en phases, où une liste de mouvements sont tirés au sort à chaque fois.  
Comme choix de mouvements il a : **F_10** (avancer de 10m), **F_20** (avancer de 20m), **F_30** (avancer de 30m), **B_10** (reculer de 10m), **T_RIGHT** (tourner à droite), **T_LEFT** (tourner à gauche), **U_TURN** (se retourner) et **ZERO** (ne rien faire).  
Chaque mouvement possède un taux d'apparition qui diminue à chaque fois que le mouvement est choisi.  <br><br>

De plus, la carte de Mars possède différents terrains qui influent sur le déplacement du rover :
- Les **plaines** qui n'ont pas d'effets.
- Les **crevasses** qui détruisent le rover.
- Les **Erg martien** qui diminuent le mouvement du rover.
- Les **Reg martien** qui diminuent de 1 le nombre de mouvement du rover à la phase suivante.

## Fonctionnalités :
- Implémentation d'un arbre n-aire où chaque noeud correspond à un mouvement potentiel fait par le rover.
- Calcul du chemin entre la feuille la plus petite d'un arbre n-aire et sa racine.
- Identification d'obstacles et applications des effets appropriés sur le rover.
- Tirage au hasard des mouvements et modification des probabilités
- Possibilité d'utiliser plusieurs maps sans problèmes
- Calcul du temps d'exécution d'une fonction
- Vérification de l'arrivée à la base
- Modification de la position du rover en fin de phase

## Utilisation :
Un code déjà inscrit dans le main.c permet de montrer le déroulement d'une manche complète où le rover tente d'atteindre sa base. Il ne s'arrête que lorsqu'il atteint la base ou lorsqu'il n'a plus de fuel.
Il suffit donc de lancer le code pour voir le jeu s'afficher.
