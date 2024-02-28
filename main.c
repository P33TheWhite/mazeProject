#include "affichage.h"
#include "game.h"
#include "structure.h"

int main(){
        Jeu jeu;
        choixMenu(lireMenu(),&jeu.options);
        initJeu(&jeu);
        jouerJeu(&jeu);
        gameOver(jeu.level,jeu.score,jeu.highScore);
        freeGame(jeu);
}