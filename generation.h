#ifndef GENERATION_H
#define GENERATION_H

#include "structure.h"

/**
 * \file Répertorie les fonctions et procédures axées sur la génération des labyrinthes et les arbres 
*/


/** 
 * \fn allouerTab1(int** tab, int taille)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Alloue les tableaux 1D
 * \param[in]  tab Pointeur Tableau 1D non alloué
 * \param[in]  taille Taille du tableau 1D
 * \param[out]  tab Tableau 1D alloué 
*/
void allouerTab1(int** tab, int taille);

/** 
 * \fn allouerTab2(int*** tab, int taille)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Alloue les tableaux 2D
 * \param[in]  tab Pointeur Tableau 2D non alloué
 * \param[in]  taille Taille du tableau 2D
 * \param[out]  tab Tableau 2D alloué 
*/
void allouerTab2(int*** tab, int taille);

/** 
 * \fn setStart( int*** matrice, int taille , int randPlacement,Joueur* j)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de générer le labyrinthe et l'arbre des chemins et placer les entrées et sorties
 * \param[in]  matrice Labyrinthe sans start
 * \param[in]  taille Jeu contenant l'intégralité des variables du jeu
 * \param[in]  randPlacement Mode de placement random droite / gauche / haut / pas 
 * \param[in]  j Joueur avec sans positions 
 * \param[out]  j Joueur avec positions placés en positions start 
 * \param[out]  matrice  Labyrinthe avec start
*/
void setStart( int*** matrice, int taille , int randPlacement,Joueur* j);

/** 
 * \fn setEnd( int*** maze, int taille, int randPlacement)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de générer le labyrinthe et l'arbre des chemins et placer les entrées et sorties
 * \param[in]  matrice Labyrinthe sans end
 * \param[in]  taille Jeu contenant l'intégralité des variables du jeu
 * \param[in]  randPlacement Mode de placement random droite / gauche / haut / pas 
 * \param[out]  maze  Labyrinthe avec end
*/
void setEnd( int*** maze, int taille, int randPlacement);

/** 
 * \fn creerMaze(Jeu* jeu)
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de générer le labyrinthe avec la méthode Randomized depth-first search
 * \param[in]  maze Jeu contenant l'intégralité des variables du jeu
 * \param[in]  taille Jeu contenant l'intégralité des variables du jeu
 * \param[out]  maze Jeu contenant le labyrinthe et l'arbre des chemins
*/
void mazeGenerator(int*** maze,int taille);

/** 
 * \fn ajouter_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'ajouter dans la pile la case visitée 
 * \param[in]  colonne Colonne actuelle
 * \param[in]  ligne Ligne actuelle
 * \param[in]  cStack Pointeur de la pile colonne
 * \param[in]  rStack Pointeur de la pile ligne
 * \param[in]  index Pointeur de l'index actuel dans le nombre de cases visitées
 * \param[out]  rStack Pile colonne modifié nouvelle case visitée
 * \param[out]  cStack Pile colonne modifié nouvelle case visitée
*/
void ajouter_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );

/** 
 * \fn retirer_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de retirer dans la pile une case visitée pour revenir sur des cases disponibles (Randomized depth-first search)
 * \param[in]  colonne Colonne actuelle
 * \param[in]  ligne Ligne actuelle
 * \param[in]  cStack Pointeur de la pile colonne
 * \param[in]  rStack Pointeur de la pile ligne
 * \param[in]  index Pointeur de l'index actuel dans le nombre de cases visitées
 * \param[out]  rStack Pile colonne modifié ancienne case visitée
 * \param[out]  cStack Pile colonne modifié ancienne case visitée
*/
void retirer_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );

/** 
 * \fn setValues( int values[ DIR ][ VALUES ], int colonne, int ligne, int taille)
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'établir les valeurs dans un tableau 2D pour définir la prochaine direction à prendre
 * \param[in]  values Tableau des valeurs autour du joueurs
 * \param[in]  colonne Colonne actuelle
 * \param[in]  ligne Ligne actuelle
 * \param[in]  taille Taille du labyrinthe
 * \param[out]  values Tableau des valeurs autour du joueurs
*/
void setValues( int values[ DIR ][ VALUES ], int colonne, int ligne, int taille);


/** 
 * \fn creerMaze(Jeu* jeu)
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de générer le labyrinthe et l'arbre des chemins et placer les entrées et sorties
 * \param[in]  jeu Jeu contenant l'intégralité des variables du jeu
 * \param[out]  jeu Jeu contenant le labyrinthe et l'arbre des chemins
*/
void creerMaze(Jeu* jeu);

/** 
 * \fn placerEvents(Maze* maze,int level)
 * \author Paul Brechenmacher / Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de placer les events de manières aléatoire dans le labyrythne
 * \param[in]  maze Labyrinthe déja généré avec une taille définie
 * \param[in]  level Niveau du joueur pour placer plus ou moins d'events
 * \param[out]  maze Labyrinthe avec des events 
*/
void placerEvents(Maze* maze,int level);

/** 
 * \fn creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze,int taille)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de manière récursive de créer un arbre des cases accessibles dans le labyrinthe
 * \param[in]  positionL Position de la ligne de la case dans le labyrinthe à rajouter dans l'arbre
 * \param[in]  positionC Position de la colonne de la case dans le labyrinthe à rajouter dans l'arbre
 * \param[in]  a Arbre avec les chemins possibles
 * \param[in]  maze Tableau contentant le labyrinthe
 * \param[in]  taille Taille du labyrinthe
 * \return Arbre avec une nouvelle case accessible dans le labyrinthe
*/
arbreChemins creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze,int taille);


/** 
 * \fn creerArbreCheminsCache(arbreChemins a, int positionL , int positionC, int** maze,arbreChemins a_parent,,int taille)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de manière récursive de créer un arbre des cases accessibles dans le labyrinthe avec son parent et ses fils
 * \param[in]  positionL Position de la ligne de la case dans le labyrinthe à rajouter dans l'arbre
 * \param[in]  positionC Position de la colonne de la case dans le labyrinthe à rajouter dans l'arbre
 * \param[in]  a Arbre avec les chemins possibles
 * \param[in]  maze Tableau contentant le labyrinthe
 * \param[in] a_parent Arbre parent permettant au joueur de revenir sur ses pas
 * \param[in]  taille Taille du labyrinthe
 * \return Arbre avec une nouvelle case accessible dans le labyrinthe
*/
arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille);

#endif