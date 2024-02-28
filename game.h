#ifndef GAME_H
#define GAME_H

#include "structure.h"

/**
 * \file Répertorie les fonctions et procédures axées sur le déroulement du jeu
*/

/** 
 * \fn initJeu(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'initialiser le jeu
 * \param[in]  jeu Jeu contenant l'intégralité des variables non initialisées du jeu
 * \param[out]  jeu Jeu initialisé
*/
void initJeu(Jeu* jeu);

/** 
 * \fn useItem(Jeu* jeu, int typeInput)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'utiliser un item dans son inventaire
 * \param[in]  typeInput Numéro de la touche appuyée pour utiliser un objet 
 * \param[in]  jeu Jeu avec inventaire avec l'item utilisé
 * \param[out]  jeu Jeu avec inventaire sans l'item utilisé
*/
void useItem(Jeu* jeu, int typeInput);

/** 
 * \fn deplacementValide(int positionL, int positionC, arbreChemins* a, Joueur j,int** maze,int taille)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 11:12 AM) 
 * \brief  Permet de valider si un déplacement est possible ou non 
 * \param[in]  positionL Position ligne demandée par le joueur
 * \param[in]  positionC Position colonne demandée par le joueur
 * \param[in]  a Arbre contenant les cases accessibles pour le joueur
 * \param[in]  j Jeu contenant la position du joueur
 * \param[in]  maze Tableau 2D représentant le labyrinthe
 * \param[in]  taille Taille du labyrinthe
 * \return 0 si déplacement invalide / 1 si déplacement valide
*/
int deplacementValide(int positionL, int positionC, arbreChemins* a, Joueur j,int** maze,int taille);

/** 
 * \fn void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze, int positions[2])
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de vérifier et effectuer les bonnes fonctions selon les actions du joueur
 * \param[in]  jeu Jeu contenant toutes la position et le labyrinthe avec les actions du joueurs
 * \param[in]  a Arbre contenant les cases accessibles pour le joueur
 * \param[in]  maze Pointeur du tableau 2D représentant le labyrinthe
 * \param[in]  positions Tableau des positions du joueur 
 * \param[out]  jeu Jeu contenant toutes la position et le labyrinthe mis à jour
*/
void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze, int positions[2]);


/** 
 * \fn gameOver(int level, int score, int highscore)
 * \author Paul Brechenmacher
 * \date  (January 8th, 2024 9:59 PM)
 * \brief  Affiche la fin de partie et sauvegarde le highscore dans un CSV
 * \param[in] level Niveau atteint par le joueur au cours de la partie
 * \param[in] score Score de la partie
 * \param[in] highscore Score le plus haut enregisté dans un CSV
*/
void gameOver(int level, int score, int highscore);

/** 
 * \fn verifEvent(Jeu* jeu, int*** maze, int positionL, int positionsC)
 * \author Paul Brechenmacher
 * \date  (January 12th, 2024 5:32 PM)
 * \brief  Vérifie si un event est placé sur la case demandé par le joueur et effectue un évenement aléatoirement
 * \param[in]  jeu Jeu contenant l'inventaire et les différentes options
 * \param[in]  maze Pointeur du tableau 2D représentant le labyrinthe  
 * \param[in]  positionL Position ligne demandée par le joueur
 * \param[in]  positionC Position colonne demandée par le joueur
*/
void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionC);

/** 
 * \fn verifCheck(Jeu* jeu, int** maze, int positionL, int positionsC)
 * \author Paul Brechenmacher
 * \date  (January 12th, 2024 5:32 PM)
 * \brief  Vérifie si la case demandée est un checkpoint
 * \param[in]  jeu Jeu contenant l'inventaire et les différentes options
 * \param[in]  maze  Tableau 2D représentant le labyrinthe  
 * \param[in]  positionL Position ligne demandée par le joueur
 * \param[in]  positionC Position colonne demandée par le joueur
*/
void verifCheck(Jeu* jeu, int** maze, int positionL, int positionC);


/** 
 * \fn eventJoueur(int* typeEvent,Joueur* j);
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Effectue l'event en vérifiant son type et l'état du joueur (souvent le poison ou le feu)
 * \param[in]  j Pointeur du Joueur contenant les caractéristiques et les états du joueur
 * \param[in]  typeEvent Type de l'event à effectuer et à vérifier
 * \param[out]  j Joueur modifié avec un nouvel état (souvent le poison ou le feu)
*/
void eventJoueur(int* typeEvent,Joueur* j);

/** 
 * \fn ajouterItemInventaire(Jeu* jeu, int type, char* name)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Ajoute un objet dans l'inventaire du joueur
 * \param[in]  jeu Jeu contenant l'inventaire 
 * \param[in]  type Type de l'objet à ajouter
 * \param[in]  name Nom de l'objet à ajouter
 * \param[out]  jeu Jeu contenant l'inventaire avec le nouvel item
*/
void ajouterItemInventaire(Jeu* jeu, int type, char* name);

/** 
 * \fn lenInt(int score)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief Calcule la longueur d'un entier
 * \param[in]  score Score du joueur
 * \return Longeur de l'entier
*/
int lenInt(int score);

/** 
 * \fn getScoreCSV(Jeu* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Récupère dans le CSV le highscore le plus haut du joueur
 * \param[in]  jeu Jeu avec le score le plus haut non initialisé
 * \param[out]  jeu Jeu contenant le score le plus haut enregistré, 0 si le fichier n'existe pas
*/
void getScoreCSV(Jeu* jeu);

/** 
 * \fn saveHighScoreCSV(int highScore, int newscore)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Enregistre dans le CSV le highscore le plus haut du joueur
 * \param[in]  highScore Plus haut score réalisé par le joueur
 * \param[in]  newscore Score de la partie actuelle
*/
void saveHighScoreCSV(int highScore, int newscore);

/** 
 * \fn placerKeys(Maze* maze, Joueur* j)
 * \author Paul Brechenmacher
 * \date  (January 8th, 2024 9:29 PM) 
 * \brief  Place les clefs dans les labyrinthes 3x3
 * \param[in]  maze Maze contenant le labyrinthe, son type et sa taille
 * \param[in]  j Joueur initialisé avec 0 clé trouvée
 * \param[out]  maze Maze contenant le labyrinthe avec la clé placée 
*/
void placerKeys(Maze* maze, Joueur* j);

/** 
 * \fn jouerMaze(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 11:12 AM)
 * \brief  Permet de lancer la partie avec les options sélectionées et de jouer
 * \param[in]  jeu Jeu avec le maze avant déplacement joueur
 * \param[out]  jeu Jeu après le déplacement joueur 
*/
void jouerMaze(Jeu* jeu);

/** 
 * \fn verifPoisonFeu(Joueur* j)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 11:12 AM) 
 * \brief  Permet d'effectuer les évenements poison et feu en influant sur la vie du joueur
 * \param[in]  j Joueur contenant sa vie et son nombre de tours restant avec EtatDanger != 0
 * \param[out]  j Joueur avec vie modifié et nombre de tours restant modifié
*/
void verifPoisonFeu(Joueur* j);

/** 
 * \fn verifEtatEvent(Joueur* j,int* typeEvent)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 11:12 AM) 
 * \brief Vérifie l'état de l'évenement pour l'affichage et la fin du poison et du feu
 * \param[in]  j Pointeur du Joueur contenant les caractéristiques et les états du joueur
 * \param[in]  typeEvent Type de l'event à effectuer et à vérifier
 * \param[out]  j Joueur modifié avec un nouvel état (souvent le poison ou le feu)
*/
void verifEtatEvent(Joueur* j,int* typeEvent);

/** 
 * \fn creerMegaMaze(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 2:11 PM)
 * \brief  Crée un labyrinthe 3x3 avec des checkpoints et des clefs
 * \param[in]  jeu Jeu sans megaMaze(labyrinthe 3x3)
 * \param[out]  jeu Jeu contenant un megaMaze avec des checkpoints et des clefs
*/
void creerMegaMaze(Jeu* jeu);

/** 
 * \fn jouerJeu(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de lancher la partie avec un jeu initialisé
 * \param[in]  jeu Jeu initialisé
 * \param[out]  jeu Jeu terminé
*/
void jouerJeu(Jeu* jeu);

/** 
 * \fn playMegaMaze(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 8th, 2024 9:59 PM) 
 * \brief  Permet de jouer avec les labyrinthes 3x3
 * \param[in]  jeu Jeu avec maze, arbreChemins et events clefs créés/placés
 * \param[out]  jeu Jeu avec maze, arbreChemins modifiés
*/
void playMegaMaze(Jeu* jeu);

/** 
 * \fn playMazeSimple(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 8th, 2024 9:59 PM) 
 * \brief  Permet de jouer avec le labyrinthe
 * \param[in]  jeu Jeu avec maze, arbreChemins et events créés/placés
 * \param[out]  jeu Jeu avec maze, arbreChemins modifiés 
*/
void playMazeSimple(Jeu* jeu);

/** 
 * \fn getOptions(Options* options,int numOptions)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 1:08 AM) 
 * \brief  Récupère à chaque selon la ligne la valeur de l'option afin d'afficher la dernière selectionée
 * \param[in]  options Options enregistré
 * \param[in]  numOptions Numéro de la ligne (0:skin / 1:mode / 2:niveau)
 * \return Type de l'ancien numId selon la ligne de l'option
*/
int getOptions(Options* options,int numOptions);

/** 
 * \fn saveOptions(Options* options,int numOptions,int numId)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 1:08 AM)
 * \brief  Permet de sauvegarder l'option selon la ligne et la valeur numId(choix du joueur pour une option)
 * \param[in]  options Options enregistré
 * \param[in]  numOptions Numéro de la ligne (0:skin / 1:mode / 2:niveau)
 * \param[in]  numId Numéro du type voulu pour l'option (ex emoji : 0 : 👾)
 * \param[out]  options Options modifié
*/
void saveOptions(Options* options,int numOptions,int numId);

/** 
 * \fn initOptions(char**** optionsTab,Options* options);
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 1:08 AM)
 * \brief  Permet d'initialiser et d'allouer les options et les tableaux du menu options  
 * \param[in]  optionsTab Tableaux 2D menu options non alloués
 * \param[in]  optionsTab Tableaux 2D menu options alloués et initialisés
 * \param[in]  options Options non initialisées
 * \param[out]  options Options initialisées par défaut
*/
void initOptions(char**** optionsTab,Options* options);

/** 
 * \fn freeGame(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 1:27 AM)
 * \brief  Permet de libérer la mémoire
 * \param[in]  jeu Jeu contenant Tableaux 2D / Arbre chemins / Inventaire alloués
 * \param[out]  jeu Jeu contenant Tableaux 2D / Arbre chemins / Inventaire libérés
*/
void freeGame(Jeu jeu);

/** 
 * \fn freeGame(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 15th, 2024 1:02 AM)
 * \brief  Permet de libérer le labyrinthe
 * \param[in]  maze Tableau 2D alloué
 * \param[in]  taille Taille du labyrinthe
 * \param[out]  maze Tableau 2D libéré
*/
void freeMaze(int** maze,int taille);

/** 
 * \fn freeGame(Jeu* jeu)
 * \author Paul Brechenmacher
 * \date  (January 15th, 2024 1:02 AM)
 * \brief  Permet de libérer l'arbre des chemins
 * \param[in]  arbre Arbre des chemins alloué
 * \param[out]  arbre Arbre des chemins libéré
*/
void freeArbre(arbreChemins arbre);




/** 
 * \fn afficherJoueur(int typeEmoji)
 * \author Paul Brechenmacher
 * \date  (January 9th, 2024 9:22 PM) 
 * \brief  Affiche le joueur en fonction du type d'émoji
 * \param[in]  int typeEmoji
*/
void afficherJoueur(int typeEmoji);


/** 
 * \fn afficherAroundPlayer(int** matrice , int n, int typeEmoji,int typeMode,Joueur joueur,int visionRange)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Afficher le labyrinthe autour du joueur
 * \param[in]  matrice Tableau 2D représentant le maze
 * \param[in]  taille,typeEmoji,typeMode taille du maze, type d'émoji et type de mode
 * \param[in]  joueur,visionRange joueur avec sa position et sa distance de vision 
 */
void afficherAroundPlayer(int** matrice , int n, int typeEmoji,int typeMode,Joueur joueur,int visionRange);
#endif