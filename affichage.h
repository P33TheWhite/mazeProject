#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structure.h"

/**
 * \file Répertorie les fonctions et procédures axées sur les affichages grpahiques
*/

/** 
 * \fn lireMenu();
 * \author Etienne Massonnet
 * \date (January 9th, 2024 5:00 PM)
 * \brief Prépare l'affichage du menu de début de jeu
 * \return  chaîne de caractères correspondant aux différents versions du menu selon le curseur de l'utilisateur
*/
char** lireMenu();

/** 
 * \fn choixMenu(char** menus, Options* options);
 * \author Etienne Massonnet
 * \date (January 9th, 2024 5:00 PM)
 * \brief Affiche le menu et propose de naviguer entre les 3 choix possibles
 * \param[in] menus, options  chaînes de caractères contenant les différents menus et le pointeur contenant les options de jeu
 * \param[out] options  options de jeu modifiées
*/
void choixMenu(char** menus, Options* options);

/** 
 * \fn regle(Options* options);
 * \author Paul Brechenmacher
 * \date (January 9th, 2024 5:00 PM)
 * \brief affiche les règles du jeu 
 * \param[in] options pointeur contenant les options de jeu
 * \param[out] options 
*/
void regle(Options* options);

/** 
 * \fn lireArsenal()
 * \author Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Lit le CSV et affiche le logo de Arsenal en mode labyrinthe
*/
void lireArsenal();

/** 
 * \fn scorePrint(int scoreLen)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'espacer correctement seulement la taille du score du joueur  
 * \param[in]  scorelen Longueur de l'entier score 
*/
void scorePrint(int scoreLen);

/** 
 * \fn afficherScore(int score, int level)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Affiche le score et le niveau du joueur
 * \param[in]  score Score du joueur
 * \param[in]  level Niveau du joueur 
*/
void afficherScore(int score, int level);

/** 
 * \fn afficherInventaire(Jeu jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'afficher l'inventaire du joueur et sa vie
 * \param[in]  jeu Jeu contenant l'inventaire du joueur et sa vie 
*/
void afficherInventaire(Jeu jeu);

/** 
 * \fn emoji(int type)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'afficher les émojis selon l'item rencontré ou utilisé
 * \param[in]  type Type d'émoji selon l'énumération itemListe
 * \return Chaine de caractère représentant l'émoji correspondant à son type 
*/
char* emoji(int type);

/** 
 * \fn afficherArbreChemins(arbreChemins a,int** maze)
 * \author Paul Brechenmacher
 * \date   (January 2nd, 2024 10:21 PM) 
 * \brief  Permet d'afficher chaque case contenus dans l'arbre des chemins
 * \param[in]  a Arbre des chemins 
 * \param[in]  maze Tableau 2D représentant le labyrinth
*/
void afficherArbreChemins(arbreChemins a,int** maze);

/** 
 * \fn afficherUseItem(int type)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet d'afficher un objet rencontré ou utilisé dans le labyrinthe 
 * \param[in] type Type d'objet utilisé ou rencontré dans le labyrinthe
*/
void afficherUseItem(int type);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet au joueur de choisir les options
 * \param[in]  options Options par défaut
 * \param[in]  optionsTab Tableau 2D pour l'affichage du menu
 * \param[out]  option Options modifiés choisis par le joueur
*/
void optionChange(Options* options, char*** optionsTab);

/** 
 * \fn afficherMatrice1(int** matrice , int taille, int typeEmoji,int typeMode)
 * \author Gabin Alquier
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Afficher le labyrinthe
 * \param[in]  matrice Tableau 2D représentant le maze
 * \param[in]  taille,typeEmoji,typeMode taille du maze, type d'émoji et type de mode
 */
void afficherMatrice1(int** matrice , int taille, int typeEmoji,int typeMode);


#endif