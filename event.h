#ifndef EVENT_H
#define EVENT_H
#include "structure.h"

extern int inversion;

/**
 * \file Répertorie les fonctions et procédures axées sur les évenements 
*/

/** 
 * \fn emptyBuffer();
 * \author Paul Le Blanc
 * \date  (January 9th, 2024 5:00 PM)
 * \brief vide le buffer
*/
void emptyBuffer();

/** 
 * \fn deplacementTouche(int etatJoueur);
 * \author Paul Le Blanc
 * \date  (January 9th, 2024 5:00 PM)
 * \brief Permet de capturer une touche utiliser par l'utilisateur et interprète cette entrée en fonction de l'état du joueur fourni et qui renvoie la touche pressée
 * \param[in] etatJoueur représentant l'etat du joueur (ETAT_ENTER, ETAT_OPTION, ETAT_MENU, ETAT_DRUNK)
 * \return caractère (touche pressée)
*/
char deplacementTouche(int etatJoueur);

/** 
 * \fn mazeCSV(Maze* maze);
 * \author Paul Le Blanc
 * \date  (January 9th, 2024 5:00 PM)
 * \brief permet d'écrire le contenue de la structure Maze dans un fichier CSV "maze.csv" placé dans le repertoire "out/"
 * \param[in] maze vers la structure Maze
*/
void mazeCSV(Maze* maze);

/** 
 * \fn mazebigCSV(Maze* megamaze, int i, int j);
 * \author Paul Le Blanc
 * \date  (January 9th, 2024 5:00 PM)
 * \brief megamaze est un labyrinthe de plusieurs labyrinthe et cette fonction permet d'écrire le contenue des différents labyrinthes dans des fichiers CSV "maze<i><j>.csv" placé dans le repertoire "out/megaMazeCSV/"
 * \parameters pointeur vers la structure Maze, entier i, entier j
  * \param[in] megamaze,i,j vers la structure Maze et la ligne et la colonne du maze
*/
void mazebigCSV(Maze* megamaze, int i, int j);

/** 
 * \fn afficherMaze(Maze *maze);
 * \author Paul Le Blanc
 * \date  (January 9th, 2024 5:00 PM)
 * \brief affiche le labyrinthe contenue dans la structure Maze dans la console
 * \parameters pointeur vers la structure Maze
 * \param[in] maze vers la structure Maze
*/
void afficherMaze(Maze *maze);

/** 
 * \fn healthPotionEvent(Jeu* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de réaliser un évenement qui soigne le joueur
 * \param[in]  Jeu Jeu contenant la vie du joueur et l'inventaire du joueur
 * \param[out]  Jeu Jeu contenant la vie augmentée du joueur ou l'inventaire du joueur modifié 
*/
void healthPotionEvent(Jeu* jeu);

/** 
 * \fn medikitEvent(Jeu* jeu)
 * \author Etienne Massonnet
 * \date  (January 9th, 2024 5:33 PM)
 * \brief  Permet de réaliser un évenement qui soigne le joueur
 * \param[in]  Jeu Jeu contenant la vie du joueur et l'inventaire du joueur
 * \param[out]  Jeu Jeu contenant la vie augmentée du joueur ou l'inventaire du joueur modifié 
*/
void medikitEvent(Jeu* jeu);

/** 
 * \fn damageTrapEvent(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'effectuer l'évenement de dégats sur le joueur
 * \param[in] jeu Jeu contenant la vie du joueur
 * \param[out] jeu Jeu contenant la vie du joueur modifiée
*/
void damageTrapEvent(Jeu* jeu);

/** 
 * \fn milkPotionEvent(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'effectuer l'évenement verre de lait (supprime les effets négatifs du joueur)
 * \param[in] jeu Jeu contenant l'inventaire et etatSobre/etatDanger du joueur
 * \param[out] jeu Jeu contenant l'inventaire et etatSobre/etatDanger du joueur modifié
*/
void milkPotionEvent(Jeu* jeu);

/** 
 * \fn naviguerArbreChemins(arbreChemins a,Maze maze,int*** tabAriane,int* x);
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 9:22 PM) 
 * \brief  (Algo A*) Permet naviguer dans l'arbre et d'incrémenter la valeur x à chaque case et de placer la valeur maximal sur la fin
 * \param[in]  a Arbre des chemins avec les cases accessibles
 * \param[in]  maze Maze contenant la taille du labyrinthe
 * \param[in]  x Valeur initialisé à 6
 * \param[in]  tabAriane Tableau 2D initialisé
 * \param[out]  x Valeur de x incrémenté ou non (accumulateur)
 * \param[out]  tabAriane Tableau 2D modifié avec des valeurs de x incrementés sur les chemins
*/
void naviguerArbreChemins(arbreChemins a,Maze maze,int*** tabAriane,int* x);

/** 
 * \fn findEnd(int** tabAriane,int* lEnd,int* cEnd,int taille)
 * \author Paul Brechenmacher
 * \date  (January 12th, 2024 6:37 PM) 
 * \brief  Permet de trouver la sortie du tabArianne
 * \param[in]  tabAriane Tableau avec des valeurs de x incrementés sur les chemins
 * \param[in]  lEnd Ligne d'arrivée non trouvée
 * \param[in]  cEnd Colonne d'arrivée non trouvée
 * \param[in]  taille Taille labyrinthe
 * \param[out]  lEnd Ligne d'arrivée trouvée
 * \param[out]  cEnd Colonne d'arrivée trouvée
*/
void findEnd(int** tabAriane,int* lEnd,int* cEnd,int taille);

/** 
 * \fn findEndArbre(int lEnd, int cEnd,arbreChemins aDebut,arbreChemins* aEnd)
 * \author Paul Brechenmacher
 * \date  (January 12th, 2024 6:37 PM)
 * \brief  Permet de trouver la sortie dans l'arbre des chemins
 * \param[in]  lEnd Ligne d'arrivée trouvée
 * \param[in]  cEnd Colonne d'arrivée trouvée
 * \param[in]  aDebut Arbre initial des chemins avec les cases accessibles
 * \param[in]  aEnd Arbre à l'arrivée du labyrinthe non trouvé
 * \param[out]  aEnd Arbre à l'arrivée du labyrinthe trouvé
*/
void findEndArbre(int lEnd, int cEnd,arbreChemins aDebut,arbreChemins* aEnd);

/** 
 * \fn remonterArbre(arbreChemins a,int** tabAriane,Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 1:27 AM)
 * \brief  Permet de trouver le chemins le plus court (algo A*), en prenant toujours la plus petite valeur aux alentours
 * \param[in]  tabAriane Arbre à l'arrivée du labyrinthe trouvé
 * \param[in]  a Arbre à l'arrivée/la fin du labyrinthe 
 * \param[in]  jeu Jeu contenant le labyrinthe
 * \param[out]  jeu Jeu contenant le labyrinthe avec le fil d'Ariane visible
*/
void remonterArbre(arbreChemins a,int** tabAriane,Jeu* jeu);

/** 
 * \fn filAriane2(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 9:22 PM) 
 * \brief  Permet d'afficher le fil d'Ariane
 * \pre Le labyrinthe doit être sans les checkpoints (typeMaze = 1) 
 * \param[in]  jeu Jeu contenant le labyrinthe
 * \param[out]  jeu Jeu contenant le labyrinthe avec le fil d'Ariane visible
*/
void filAriane2(Jeu* jeu);


#endif