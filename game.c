#include "game.h"
#include "affichage.h"
#include "event.h"
#include "generation.h"

void modeHealth(int* pvHealth, int typeMode){
    switch (typeMode) {
        case 0:
            *pvHealth = 10;
            break;
        case 1:
            *pvHealth = 1;
            break;
        case 2:
            *pvHealth = 20;
            break;
        case 3:
            *pvHealth = 10;
            break;
        case 4:
            *pvHealth = 10;
            break;
        default:
            printf("Erreur Vie");
            break;
    
    }
}

void initJeu(Jeu* jeu){
    
    jeu->maze.typeMaze = 1;
    jeu->posMaze[0] = 1;
    jeu->posMaze[1] = 0;
    jeu->level = 0;
    jeu->score = 0;
    jeu->maze.sizeMaze = INITIALSIZE;
    modeHealth(&jeu->j.pvHealth,jeu->options.typeMode);
    jeu->j.findKeys = 1;
    jeu->j.etatCheckPoint = 1;
    jeu->typeEvent = NONE;
    jeu->j.inventaire = malloc(5*sizeof(Item)); //5 items max
    for(int nbItems = 0;nbItems < 5; nbItems++){
        jeu->j.inventaire[nbItems].type = NONE;
    }
    if(jeu->options.typeMode == 4){
        jeu->j.visionRange = 2;
    }
    jeu->maze.tabMaze = NULL;
    getScoreCSV(jeu);
    srand(time(NULL));
}



void jouerMaze(Jeu* jeu){
    system("clear");
    afficherScore(jeu->level,jeu->score);
    if(jeu->options.typeMode == 4){
        afficherAroundPlayer(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji,jeu->options.typeMode,jeu->j,jeu->j.visionRange);
    }else{
        afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji,jeu->options.typeMode);
    }
    afficherInventaire(*jeu);
    eventJoueur(&jeu->typeEvent,&jeu->j);
    deplacementMaze(jeu,&jeu->maze.arbreChemin,&jeu->maze.tabMaze,jeu->j.positions);

}

int deplacementValide(int positionL, int positionC, arbreChemins* a,Joueur j,int** maze,int taille){
    int val = 0;
    
    if(positionL > -1 && positionC > -1 && positionC < taille && positionL < taille){
        if(maze[positionL][positionC] == END){
            if(!j.findKeys){
                return 0;
            }
        }
    }

    for(int n = 0; n < (*a)->nbFils; n++){
        if((*a)->fils[n]->positions[0] == positionL && (*a)->fils[n]->positions[1] == positionC){
            *a = (*a)->fils[n];
            val = 1;
            
        }
    }
    if((*a)->parent->positions[0] == positionL && (*a)->parent->positions[1] == positionC){
            *a = (*a)->parent;
            val =  1;
        }
    
    return val;
}

void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze,int positions[2]){
    switch (deplacementTouche(jeu->j.etatSobreJoueur)) {
                case HAUT:
                    if(deplacementValide(positions[0]-1,positions[1],a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0]-1,positions[1]);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0]-1,positions[1]);
                            (*maze)[positions[0]-1][positions[1]] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[0]--;

                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    }
                    break;
                case DROITE:
                    if(deplacementValide(positions[0],positions[1]+1,a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0],positions[1]+1);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0],positions[1]+1);
                            (*maze)[positions[0]][positions[1]+1] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[1]++;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    } 
                    break;
                case GAUCHE:
                    if(deplacementValide(positions[0],positions[1]-1,a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0],positions[1]-1);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0],positions[1]-1);
                            (*maze)[positions[0]][positions[1]-1] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[1]--;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    }
                    break;
                case BAS:
                    if(deplacementValide(positions[0]+1,positions[1],a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0]+1,positions[1]);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0]+1,positions[1]);
                            (*maze)[positions[0]+1][positions[1]] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[0]++;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    }
                    break;
                case HOTBAR1:
                    useItem(jeu,0);
                    break;
                case HOTBAR2:
                    useItem(jeu,1);
                    break;
                case HOTBAR3:
                    useItem(jeu,2);
                    break;
                case HOTBAR4:
                    useItem(jeu,3);
                    break;
                case HOTBAR5:
                    useItem(jeu,4);
                    break;

                default:
                printf("Invalid direction\n");
                    break;

            }
}

void playMazeSimple(Jeu* jeu){
    creerMaze(jeu);
    //mazeCSV(&jeu->maze);
    placerEvents(&jeu->maze,jeu->level);
    while(jeu->maze.arbreChemin->type && jeu->j.pvHealth > 0){
        jouerMaze(jeu);
    }
}
void playMegaMaze(Jeu* jeu){
    creerMegaMaze(jeu);
    jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]];
    jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
    for(int i = 0; i < 3 ;i++){
        for(int j = 0; j < 3;j++){
            placerEvents(&jeu->megamaze[i][j],jeu->level/2);
            //mazebigCSV(&jeu->megamaze[i][j],i,j);
            }
        }
    placerKeys(&jeu->megamaze[rand() % 3][rand() % 3],&jeu->j);
    while((!jeu->j.findKeys || jeu->maze.arbreChemin->type) && jeu->j.pvHealth > 0){
        jouerMaze(jeu);
    }
}

void jouerJeu(Jeu* jeu){
    while(jeu->j.pvHealth > 0){
        if((jeu->level/2)+1 >= ((jeu->options.typeLevel+1)*2)){ // niveau 1 2 3 4 5 6  7 / level  0 2 4 6 8 10 12  / typ 0 1 2 3 / lvl 3 5 7 9
            jeu->maze.typeMaze = 0; // 
        }
        
        if (jeu->maze.typeMaze){
            playMazeSimple(jeu);
        }else{
            playMegaMaze(jeu);
        }
        
        if(jeu->j.pvHealth > 0){
            free(jeu->maze.tabMaze);
            free(jeu->maze.arbreChemin);
            jeu->level=jeu->level+2;
            jeu->score= jeu->score + (25*jeu->level);
        }
        freeGame(*jeu);
    }
}


void gameOver(int level, int score,int highScore){    
    system("clear");
    saveHighScoreCSV(highScore,score);
    afficherScore(level,score);
    printf("\e[1;92m""⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁\n");
    printf("⠀⠀⠀⠀⠀⠀⣀⣀⣄⣀⠀⠀⠀⠀⣶⣶⣦⠀⠀⠀⠀⣼⣿⣿⡇⠀⣠⣿⣿⣿⠇⣸⣿⣿⣧⣤⠀⠀⠀\n");
    printf("⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁⠀⠀\n");
    printf("⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀\n");
    printf("⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀\n");
    printf("⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀\n");
    printf("⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀\n");
    printf("⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀\n");
    printf("⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀\n");
    printf("⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n""\e[0m");
    printf(BWHT"\n\n          Merci d'avoir joué !\n"reset);    
    sleep(5);
}

void getScoreCSV(Jeu* jeu){
    FILE* scoreFile = NULL;
    int highScore; 
    char ligne[20];
    scoreFile = fopen("./out/score.csv", "r");
    if (scoreFile == NULL) {
        highScore = 0;
        printf("Erreur ouverture fichier \n");
    }else{
        highScore = atoi(fgets(ligne,20,scoreFile));
        fclose(scoreFile);
    }
    jeu->highScore = highScore;
}

void saveHighScoreCSV(int highScore,int score){
    FILE* scoreFile = NULL;
    scoreFile = fopen("./out/score.csv", "w");
    if (scoreFile == NULL) {
        printf("Erreur ouverture fichier \n");
    }else{
        if(score > highScore){
            fprintf(scoreFile,"%d",score);
        }else{
            fprintf(scoreFile,"%d",highScore);
        }
        fclose(scoreFile);
    }
}

void initOptions(char**** optionsTab,Options* options){
    options->typeEmoji = 0;
    options->typeLevel = 1;
    options->typeMode = 0;

    (*optionsTab) = malloc(3*sizeof(char**));
    for (int i=0; i<3; i++){
        (*optionsTab)[i]=malloc(4*sizeof(char*));
        for (int j=0; j<5; j++){
        (*optionsTab)[i][j]=malloc(100*sizeof(char));
    }
    }
    (*optionsTab)[0][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 👾 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 🤡 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 💎 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][3] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 👽 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][4] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ ⚽ ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";

    
    
    
    (*optionsTab)[1][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║  "BWHT"◀ NORMAL ▶"BPUR"  ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║   "BWHT"◀ HARD ▶"BPUR"   ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║   "BWHT"◀ EASY ▶"BPUR"   ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][3] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║  "BWHT"◀ BONUS ▶"BPUR"   ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][4] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║  "BWHT"◀ PLAYER ▶"BPUR"  ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";


    (*optionsTab)[2][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 2 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 4 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 6 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][3] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 8 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][4] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║    "BWHT"◀ 10 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";

}

void saveOptions(Options* options,int numOptions,int numId){
    switch (numOptions) {
        case 0:
            options->typeEmoji = numId;
            break;
        case 1:
            options->typeMode = numId;
            break;
        case 2:
            options->typeLevel = numId;
            break;
    }
}

int getOptions(Options* options,int numOptions){
    switch (numOptions) {
        case 0:
            return options->typeEmoji;
        case 1:
            return options->typeMode;
        case 2:
            return options->typeLevel;
        default:
            return 0;
    } 
}



void freeArbre(arbreChemins arbre){
    for(int n = 0; n < (arbre)->nbFils; n++){
        freeArbre((arbre)->fils[n]);
        free(arbre);
    }
}

void freeMaze(int** maze,int taille){
    for(int i = 0; i < taille;i++){
        free(maze[i]);
    }
    free(maze);
}


void freeGame(Jeu jeu){
    // if (jeu.maze.typeMaze){
    //     for (int i = 0; i < jeu.maze.sizeMaze; i++) {
    //         for (int j = 0; j < jeu.maze.sizeMaze; j++) {
    //             printf("%d ", jeu.maze.tabMaze[i][j]);
    //         }
    //         printf("\n");
    //     }
    //     freeMaze(jeu.maze.tabMaze,jeu.maze.sizeMaze);
    //     }else{
    //         for(int i = 0; i < 3;i++){
    //             for(int j = 0; j < 3;j++){
    //             freeMaze(jeu.megamaze[i][j].tabMaze,jeu.megamaze[i][j].sizeMaze);
    //             }
    //         }  
    //     }
    // freeArbre(jeu.maze.arbreChemin);
}



