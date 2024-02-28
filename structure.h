#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>
#include "stdio.h"

typedef enum {NONE,HEALTH,MEDIKIT,DAMAGE,FIRE,DRUNK,MILK,ARIANE,POISON,SCORE,FUN,KEY_ITEM}itemListe;
typedef enum {ETAT_NORMAL,ETAT_DRUNK,ETAT_MENU,ETAT_ENTER,ETAT_OPTION}etatListe;
typedef enum {ETAT_NON_DANGER,ETAT_FEU,ETAT_POISON}lifeListe;


#define N 1000
#define BGRN "\e[1;32m"
#define BRED "\e[1;31m"
#define BWHT "\e[1;37m"
#define BPUR "\e[1;96m"	
#define reset "\e[0m"


#define HAUT 122
#define BAS 115
#define GAUCHE 113
#define DROITE 100
#define HOTBAR1 49
#define HOTBAR2 50
#define HOTBAR3 51 
#define HOTBAR4 52
#define HOTBAR5 53
#define ENTER 13


#define WALL 0
#define SPACE 1
#define END 2
#define START 3
#define PLAYER 3
#define KEY 4
#define EVENT 5
#define CHECKPOINT 6
#define FIL 7   
#define BLUE 9
#define WHITE 8
#define N 1000

#define DIR 4
#define VALUES 19
#define INITIALSIZE 7

struct Item{
    int type; //itemListe
    char* name;
};
typedef struct Item Item;
struct Joueur{
    int pvHealth;
    Item* inventaire;
    int positions[2];
    int etatSobreJoueur; // ETAT_NORMAL,ETAT_DRUNK,ETAT_MENU,ETAT_ENTER,ETAT_OPTION
    int etatDangerJoueur; // ETAT_NON_DANGER,ETAT_FEU,ETAT_POISON
    int etatTourRestants;
    int etatCheckPoint; // 1 pas de checkpoint //0 checkpoint en cours // 2 ancien checkpoint
    int findKeys; // 0 = NON et 1 = OUI
    int visionRange;
};
typedef struct Joueur Joueur;

typedef struct node {
  int positions[2];
  int nbFils;
  int type; //2 si CHECK 1 si SPACE et 0 si END
  struct node** fils;
  struct node* parent;
}node;
typedef node* arbreChemins;

struct Maze{
    int typeMaze; // NORMAL = 1 / AVEC CLES = 0 / 2 = bonus
    int sizeMaze;
    int** tabMaze;
    arbreChemins arbreChemin;
    arbreChemins arbreCheminDepart;

};
typedef struct Maze Maze;

struct Options{
    int typeEmoji; //👾 🤡 💎 👽
    int typeMode; // NORMAL HARD EASY BONUS 
    int typeLevel; // " 2 4 6 8 10
};
typedef struct Options Options;


struct Jeu{
    int typeEvent; // NONE = 0 else afficher use item
    Joueur j;
    int level;
    int score;
    int highScore;
    int posMaze[2];
    Maze maze;
    Maze** megamaze;
    Options options;
};
typedef struct Jeu Jeu;



#endif