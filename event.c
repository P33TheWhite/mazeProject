#include "event.h"
#include "affichage.h"
#include "generation.h"

void emptyBuffer() {
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
}

char deplacementTouche(int etatJoueur){
  struct termios tty_opts_backup, tty_opts_raw;
  char c;
  int pastermine=1;//par défaut on le met à vrai


  // Back up current TTY settings
  tcgetattr(STDIN_FILENO, &tty_opts_backup);

  // Change TTY settings mode
  cfmakeraw(&tty_opts_raw);
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

  while (pastermine) {


    c = getchar();

    if (etatJoueur == ETAT_ENTER){
      switch(c){
        case ENTER:
          pastermine =0;
          break;
        default:
          break;
      }
    }

    if (etatJoueur == ETAT_OPTION) {
      switch (c) {
        case HAUT:
          pastermine = 0;
          break;
        case BAS:
          pastermine = 0;
          break;
        case ENTER:
          pastermine = 0;
          break;
        case DROITE:
          pastermine = 0;
          break;
        case GAUCHE:
          pastermine = 0;
          break;

        default:
          break;
      }
    }


    if (etatJoueur == ETAT_MENU) {
      switch (c) {
        case HAUT:
          pastermine = 0;
          break;
        case BAS:
          pastermine = 0;
          break;
        case ENTER:
          pastermine = 0;
          break;

        default:
          break;
      }
    }
    
    if (etatJoueur == ETAT_DRUNK) {
      switch (c) {
        case HAUT:
          c = BAS;
          pastermine = 0;
          break;
        case GAUCHE:
          c = DROITE;
          pastermine = 0;
          break;
        case DROITE:
          c = GAUCHE;
          pastermine = 0;
          break;
        case BAS:
          c = HAUT;
          pastermine = 0;
          break;
        case HOTBAR1: 
          pastermine=0;
          break;
        case HOTBAR2:
          pastermine=0;
          break;
        case HOTBAR3:
          pastermine=0;
          break;
        case HOTBAR4:
          pastermine=0;
          break;
        case HOTBAR5:
          pastermine=0;
          break;
        default:
          break;
      }
    }
    
    switch(c){
      case HAUT:
        pastermine=0;
        break;
      case GAUCHE:
        pastermine=0;
        break;
      case DROITE:
        pastermine=0;
        break;
      case BAS:
        pastermine=0;
        break;
      case HOTBAR1:
        pastermine=0;
        break;
      case HOTBAR2:
        pastermine=0;
        break;
      case HOTBAR3:
        pastermine=0;
        break;
      case HOTBAR4:
        pastermine=0;
        break;
      case HOTBAR5:
        pastermine=0;
        break;
      case 97:
        printf("\n Vous avez tapé la lettre %c qui permet de quitter le programme!",c);
      
        /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
        // Restore previous TTY settings
        tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
        printf("\n");
        exit(0);
      default:
        printf("NON prise en compte\r\n");
        break;
    }
  }


  /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
  // Restore previous TTY settings
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

  return c;

}


void mazeCSV(Maze* maze) {
    FILE *fichier = fopen("out/maze.csv", "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier");
    }
    for(int i=0;i<(maze->sizeMaze);i++){
      for(int j=0;j<(maze->sizeMaze);j++){
        fprintf(fichier,"%d ",maze->tabMaze[i][j]);
      }
      fprintf(fichier, "\n");
    }

    fclose(fichier);
}


void mazebigCSV(Maze* maze, int i, int j) {
    char fichiers[40];
    snprintf(fichiers, sizeof(fichiers), "./out/megaMazeCSV/maze%d%d.csv",i,j);
    FILE *fichier = fopen(fichiers, "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier");
    }
    for(int i=0;i<maze->sizeMaze;i++){
      for(int j=0;j<maze->sizeMaze;j++){
        fprintf(fichier,"%d ",maze->tabMaze[i][j]);
      }
      fprintf(fichier, "\n");
    }

    fclose(fichier);
}

void afficherMaze(Maze *maze) {
    for (int i = 0; i < maze->sizeMaze; i++) {
        for (int j = 0; j < maze->sizeMaze; j++) {
            printf("%2d ", maze->tabMaze[i][j]);
        }
        printf("\n");
    }
}

void ajouterItemInventaire(Jeu* jeu, int type, char* name){
    int nbItems = 0;
    while(jeu->j.inventaire[nbItems].type != NONE){
        nbItems++;
    }
    jeu->j.inventaire[nbItems].type = type;
    jeu->j.inventaire[nbItems].name = name;
}

// void funEventTest(){
//     system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ &");
//     system("sleep 2");  
//     system("clear");     
// }

void healthPotionEvent(Jeu* jeu){
    if(jeu->j.pvHealth > 8){
        ajouterItemInventaire(jeu,HEALTH,"Health Potion");
    }else{
        jeu->j.pvHealth = jeu->j.pvHealth +2;
    }
}

void medikitEvent(Jeu* jeu){
    if(jeu->j.pvHealth > 5){
        ajouterItemInventaire(jeu,MEDIKIT,"Medikit");
    }else{
        jeu->j.pvHealth = jeu->j.pvHealth +5;
    }
}

void damageTrapEvent(Jeu* jeu){
    jeu->j.pvHealth--;
}


void milkPotionEvent(Jeu* jeu){
    if(jeu->j.etatSobreJoueur || jeu->j.etatDangerJoueur){
        if(jeu->j.etatSobreJoueur && jeu->options.typeMode == 4){
            jeu->j.visionRange++;
        }
        jeu->j.etatSobreJoueur=ETAT_NORMAL;
        jeu->j.etatDangerJoueur=ETAT_NON_DANGER;
        
    }else{
        ajouterItemInventaire(jeu,MILK,"Milk Potion");
    }

}

void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionC){
    if((*maze)[positionL][positionC] == EVENT){
        jeu->score = jeu->score + 25;
        int precEvent =-1;
        int randomEvent;
        usleep(5000);
        // pas remettre l'inversion clavier si on l'a pas enlevé avant
        do{
            randomEvent = (rand() % 10)+1; // entre random entre 1 et 10
        }while (precEvent==randomEvent);
        precEvent = randomEvent;
        
        switch (randomEvent) {
            case HEALTH:
                healthPotionEvent(jeu);
                break;
            case MEDIKIT:
                medikitEvent(jeu);
                break;
            case DAMAGE:
                damageTrapEvent(jeu);
                break;
            case FIRE:
                jeu->j.etatDangerJoueur = ETAT_FEU;
                jeu->j.etatTourRestants = jeu->j.etatTourRestants + (jeu->level/4)+1;
               break;
            case DRUNK:
                jeu->j.etatSobreJoueur=ETAT_DRUNK;
                if(jeu->options.typeMode == 4){
                    if(jeu->j.visionRange > 2){
                        jeu->j.visionRange--;
                    }
                }
                precEvent=1;
                break;
            case MILK:
                milkPotionEvent(jeu);
                break;
            case ARIANE:
                if(jeu->maze.typeMaze){
                    filAriane2(jeu);
                }
                break;
            case POISON:
                jeu->j.etatDangerJoueur = ETAT_POISON;
                jeu->j.etatTourRestants = jeu->j.etatTourRestants + (jeu->level/4)+2;
                break;
            case SCORE:
                jeu->score = jeu->score + 500;
                break;
            case FUN:
                if(jeu->options.typeEmoji == 1 && jeu->options.typeMode == 3){
                    system("clear");
                    lireArsenal();
                    sleep(5);
                    system("clear");
                }else{
                    jeu->score = jeu->score + 250;
                    if(jeu->options.typeMode == 4){
                            jeu->j.visionRange++;
                    }
                }
                break;

            default:
                printf("Error Event Switch Case\n");
                break;
        }
        jeu->typeEvent = randomEvent;
    }
    if((*maze)[positionL][positionC] == KEY){
        jeu->j.findKeys = 1;
        jeu->score = jeu->score + 100;
    }
}


void verifPoisonFeu(Joueur* j){
    if(j->etatDangerJoueur != ETAT_NON_DANGER){
            if(j->etatDangerJoueur == ETAT_POISON){
                afficherUseItem(POISON);
                j->pvHealth--;
                j->etatTourRestants--;
            }
            if(j->etatDangerJoueur == ETAT_FEU){
                j->pvHealth--;
                afficherUseItem(FIRE);
                j->etatTourRestants--;
            }
        }
}

void verifEtatEvent(Joueur* j,int* typeEvent){
    // Afficher l'event en cours si pas NONE et si le joueur n'est pas en poison ou en feu
    if(*typeEvent != NONE && j->etatDangerJoueur == ETAT_NON_DANGER){
                afficherUseItem(*typeEvent);
                *typeEvent = NONE;
    }
    //Si le nombre de tours de poison et de feu est terminé
    if(j->etatTourRestants == 0){
        j->etatDangerJoueur = ETAT_NORMAL;
    }
}

void eventJoueur(int* typeEvent,Joueur* j){
    verifEtatEvent(j,typeEvent);
    verifPoisonFeu(j);
}

void useItem(Jeu* jeu, int typeInput){
    switch (jeu->j.inventaire[typeInput].type){
        case HEALTH:
            jeu->j.pvHealth = jeu->j.pvHealth +2;
            break;
        case MEDIKIT:
            jeu->j.pvHealth = jeu->j.pvHealth +5;
            break;
        case MILK:
            if(jeu->j.etatSobreJoueur && jeu->options.typeMode == 4){
                jeu->j.visionRange++;
            }
            jeu->j.etatSobreJoueur = ETAT_NORMAL;
            jeu->j.etatDangerJoueur = ETAT_NON_DANGER;
            break;
        default:
            break;
    }
    jeu->j.inventaire[typeInput].type = NONE;
}

void naviguerArbreChemins(arbreChemins a,Maze maze,int*** tabAriane,int* x){
    if(a->type == SPACE){
      (*tabAriane)[a->positions[0]][a->positions[1]] = *x;
      (*x)++;
    }else{
      (*tabAriane)[a->positions[0]][a->positions[1]] = maze.sizeMaze*maze.sizeMaze;
    }
    
    for(int n = 0; n < a->nbFils; n++){
        naviguerArbreChemins(a->fils[n],maze,tabAriane,x);
    }
}

void findEnd(int** tabAriane,int* lEnd,int* cEnd,int taille){ 
  for(int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      if(tabAriane[i][j] == taille*taille){
        *lEnd = i;
        *cEnd = j;
      }
     }
  }
}
void findEndArbre(int lEnd, int cEnd,arbreChemins aDebut,arbreChemins* aEnd){
    if(aDebut->positions[0] == lEnd && aDebut->positions[1] == cEnd){
      (*aEnd) = aDebut;
    }
    for(int n = 0; n < aDebut->nbFils; n++){
        findEndArbre(lEnd,cEnd,aDebut->fils[n],aEnd);
    }
}

void remonterArbre(arbreChemins a,int** tabAriane,Jeu* jeu){
    if(tabAriane[a->positions[0]][a->positions[1]] != 6){
      int valMin = tabAriane[a->positions[0]][a->positions[1]];
      int idMin = 0;

      for(int n = 0; n < a->nbFils; n++){
        if(tabAriane[a->fils[n]->positions[0]][a->fils[n]->positions[1]]<valMin){
          valMin = tabAriane[a->fils[n]->positions[0]][a->fils[n]->positions[1]];
          idMin = n;
        }
      }
      if(tabAriane[a->parent->positions[0]][a->parent->positions[1]]<valMin){
        valMin = tabAriane[a->parent->positions[0]][a->parent->positions[1]];
        idMin = 4;
      }
      if(idMin == 4){
        if(jeu->maze.tabMaze[a->parent->positions[0]][a->parent->positions[1]] == SPACE){
            jeu->maze.tabMaze[a->parent->positions[0]][a->parent->positions[1]] = FIL;
        }
        remonterArbre(a->parent,tabAriane,jeu);
      }else{
         if(jeu->maze.tabMaze[a->fils[idMin]->positions[0]][a->fils[idMin]->positions[1]] == SPACE){
            jeu->maze.tabMaze[a->fils[idMin]->positions[0]][a->fils[idMin]->positions[1]] = FIL;
        }
        remonterArbre(a->fils[idMin],tabAriane,jeu);
      }
  }
}


void filAriane2(Jeu* jeu){
    int x = 6;
    int** tabAriane = NULL;
    int cEnd,lEnd;

    allouerTab2(&tabAriane,jeu->maze.sizeMaze);
    naviguerArbreChemins(jeu->maze.arbreCheminDepart,jeu->maze,&tabAriane,&x);
    findEnd(tabAriane,&lEnd,&cEnd,jeu->maze.sizeMaze);
    arbreChemins aEnd = malloc(sizeof(node*));
    findEndArbre(lEnd,cEnd,jeu->maze.arbreCheminDepart,&aEnd);
    remonterArbre(aEnd,tabAriane,jeu);

}

