#include "generation.h"
#include "affichage.h"

// Choisir une ligne de départ aléatoire dans la première colonne
void setStart( int*** maze, int taille , int randPlacement, Joueur* j) {
    int random = 0;
    random = 1 + rand() % ( taille - 2 );
    // Vérifier que la case choisie est vide (pas un mur)

    // Marquer la case de départ dans la matrice et la retourner
    switch (randPlacement) {
        case 2:
                while ( (*maze)[ random ][ 1 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ 0 ] = START;
                j->positions[0] = random;
                j->positions[1] = 0;
            break;
        case 3:
            while ( (*maze)[ taille - 2  ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ taille - 1 ][ random ] = START;
                j->positions[0] = taille-1;
                j->positions[1] = random;
            break;
        case 0:
                while ( (*maze)[ random ][ taille - 2 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ taille - 1 ] = START;
                j->positions[0] = random;
                j->positions[1] = taille-1;   
            break;
        case 1:
            while ( (*maze)[ 1 ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ 0 ][ random ] = START;
                j->positions[0] = 0;
                j->positions[1] = random;
            break;
        default:
            break;
    
    }
    (*maze)[ j->positions[0] ][ j->positions[1] ] = PLAYER;
}

void setEnd(int*** maze, int taille,int randPlacement) {
    int random = 0;    
    // Choisir une ligne de fin aléatoire dans la dernière colonne
    random = 1 + rand() % ( taille - 2 );
    switch (randPlacement) {
        case 0:
                while ( (*maze)[ random ][ 1 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ 0 ] = END;
            break;
        case 1:
            while ( (*maze)[ taille - 2  ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ taille - 1 ][ random ] = END;
            break;
        case 2:
                while ( (*maze)[ random ][ taille - 2 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ taille - 1 ] = END;    
            break;
        case 3:
            while ( (*maze)[ 1 ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ 0 ][ random ] = END;
            break;
        default:
            break;
    
    }
    // Vérifier que la case choisie est vide (pas un mur)

}

void allouerTab1(int** tab, int taille){
    int n = (taille*taille);
    *tab = (int*)malloc(n * sizeof(int));
    for (int i= 0; i < n; i++) {
        (*tab)[i] = 0;  // Initialiser la matrice avec des murs (-1)
        }
    }


void allouerTab2(int*** tab, int taille){
    *tab = (int**)malloc(taille * sizeof(int*));
    for (int ligne = 0; ligne < taille; ligne++) {
        (*tab)[ligne] = (int*)malloc(taille * sizeof(int));
        for (int colonne= 0; colonne < taille; colonne++) {
            (*tab)[ligne][colonne] = WALL;  // Initialiser la matrice avec des murs (-1)
        }
    }
}

void mazeGenerator(int*** maze,int taille) {
    
    int ligne;
    int colonne;
    int index = 0;
    int *indexPtr = &index;
    int* cStack = NULL;
    int* rStack = NULL;
    int direction;
    int cont = 4;
    int maze_dir[ 4 ] = { 0 };
    int values[ DIR ][ VALUES ] = { 0 };
    int x;
    int set = 0;

    allouerTab1(&cStack, taille);
    allouerTab1(&rStack, taille);
    allouerTab2(maze,taille);

    ligne = 3;
    colonne = 5;
    

    (*maze)[ ligne ][ colonne ] = 1;

    ajouter_pile( ligne, colonne, &cStack, &rStack, indexPtr );

    srand( time( NULL ) );
    while(index >= 1) {
        while(cont != 0) {
            while( cont > 0 ) {
                set = 0;
                direction = ( 1 + rand() % DIR ) - 1;
                if ( maze_dir[ direction ] == 0 ) {
                    maze_dir[ direction ] = 1;
                    cont--;

                    setValues( values, ligne, colonne,taille);
                    for ( x = 0; x < DIR; ++x ) {
                        if ( direction == x && (*maze)[values[x][0]][values[x][1]] !=SPACE && (*maze)[values[x][2]][values[x][3]] !=SPACE && (*maze)[values[x][4]][values[x][5]] !=SPACE && (*maze)[values[x][6]][values[x][7]] !=SPACE && (*maze)[values[x][8]][values[x][9]] !=SPACE && (*maze)[values[x][10]][values[x][11]] !=SPACE && (*maze)[values[x][12]][values[x][13]] !=SPACE && (*maze)[values[x][14]][values[x][15]] !=SPACE && (*maze)[values[x][16]][values[x][17]] !=SPACE && values[x][18] ) {
                            ligne = values[ x ][ 0 ];
                            colonne = values[ x ][ 1 ];
                            (*maze)[ ligne ][ colonne ] = SPACE;
                            setValues( values, ligne, colonne,taille);
                            ligne = values[ x ][ 0 ];
                            colonne = values[ x ][ 1 ];
                            (*maze)[ ligne ][ colonne ] = SPACE;
                            ajouter_pile( ligne, colonne, &cStack, &rStack, indexPtr );
                            cont = 4;
                            set = 1;
                            break;
                        }
                    }
                    if ( set == 1 ) {
                        break;
                    }
                }

            }
            maze_dir[ 0 ] = 0;
            maze_dir[ 1 ] = 0;
            maze_dir[ 2 ] = 0;
            maze_dir[ 3 ] = 0;
        }
            retirer_pile( ligne, colonne, &cStack, &rStack, indexPtr );
            ligne = cStack[ index ];
            colonne = rStack[ index ];
            maze_dir[ 0 ] = 0;
            maze_dir[ 1 ] = 0;
            maze_dir[ 2 ] = 0;
            maze_dir[ 3 ] = 0;
            cont = 4;
    }
}

void setValues( int values[ DIR ][ VALUES ], int ligne, int colonne, int taille) {

    // Initialiser le tableau de valeurs en fonction de la position actuelle
    int Table[ DIR ][ VALUES ] = {  { ligne, colonne + 1, ligne, colonne + 2, ligne, colonne + 3, ligne - 1, colonne + 1, ligne + 1, colonne + 1, ligne + 1, colonne + 2, ligne - 1, colonne + 2, ligne - 1, colonne + 3, ligne + 1, colonne + 3, colonne < ( taille - 2 ) },
                                 { ligne, colonne - 1, ligne, colonne - 2, ligne, colonne - 3, ligne - 1, colonne - 1, ligne - 1, colonne - 2, ligne - 1, colonne - 3, ligne + 1, colonne - 1, ligne + 1, colonne - 2, ligne + 1, colonne - 3, colonne > 1 },
                                 { ligne - 1, colonne, ligne - 2, colonne, ligne - 3, colonne, ligne - 1, colonne + 1, ligne - 2, colonne + 1, ligne - 3, colonne + 1, ligne - 1, colonne - 1, ligne - 2, colonne - 1, ligne - 3, colonne - 1, ligne > 1 },
                                 { ligne + 1, colonne, ligne + 2, colonne, ligne + 3, colonne, ligne + 1, colonne + 1, ligne + 2, colonne + 1, ligne + 3, colonne + 1, ligne + 1, colonne - 1, ligne + 2, colonne - 1, ligne + 3, colonne - 1, ligne < ( taille - 2 ) } };
    int x, y;
    // Copier les valeurs de Table dans values
    for ( x = 0; x < DIR; ++x ) {
        for ( y = 0; y < VALUES; ++y ) {
            if(Table[ x ][ y ] >= 0 && Table[x][y] < taille){
                values[ x ][ y ] = Table[ x ][ y ];
            }else{
                values[ x ][ y ] = 0;
            }
        }
    }
}

void ajouter_pile( const int ligne, const int colonne, int** cStack, int** rStack, int *index ) {
    // Ajouter la position actuelle à la pil
    (*cStack)[ *index ] = ligne;
    (*rStack)[ *index ] = colonne;
    *index += 1;
}

void retirer_pile( const int ligne, const int colonne, int** cStack, int** rStack, int *index ) {
    // Retirer la position actuelle de la pile
    (*cStack)[ *index ] = ligne;
    (*rStack)[ *index ] = colonne;
    *index -= 1;
}


arbreChemins creerArbreChemins(arbreChemins a, int positionL, int positionC,  int** maze,int taille){
    arbreChemins a_parent;
    a_parent = malloc(sizeof(node));
    a_parent->nbFils = 1;
    a_parent->positions[0] = positionL;
    a_parent->positions[1] = positionC;
    return creerArbreCheminsCache(a,positionL,positionC,maze,a_parent,taille);
}


arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille){
        a = malloc(sizeof(node));
        a->fils = malloc(1 * sizeof(node*));
        a->positions[0] = positionL;
        a->positions[1] = positionC;
        a->parent = a_parent;
        a->nbFils = 0;
        //afficherMatrice(maze, SIZE);
        if(maze[a->positions[0]][a->positions[1]] == END){
            a->type = 0;
        }else{
            if(maze[a->positions[0]][a->positions[1]] == CHECKPOINT){
                a->type = 2;
            }else{
                a->type = 1;

            }
        }
        
        
        if(positionC != taille-1){
            if(maze[a->positions[0]][a->positions[1]+1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]+1 != a->parent->positions[1])){ //DROITE
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC+1,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
            }

        }
        if(positionL != taille-1){
            if(maze[a->positions[0]+1][a->positions[1]] >= SPACE && (a->positions[0]+1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ // BAS
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL+1, positionC,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
            
            }
        }

        if(positionL != 0){
            if(maze[a->positions[0]-1][a->positions[1]] >= SPACE && (a->positions[0]-1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ //HAUT
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL-1, positionC,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;

            }
        }

        if(positionC != 0){
            if(maze[a->positions[0]][a->positions[1]-1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]-1 != a->parent->positions[1])){ //GAUCHE
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC-1,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
                return a;
            }
            return a;


        }
        
        return a;
    }



void mazePlacementSimple(int*** maze,int taille,Joueur* j){
    int randPlacement = rand() % 4; // 0 1 2 3

    setEnd(maze,taille,randPlacement);
    setStart(maze,taille,randPlacement,j);

}

void setCheck( int*** maze, int taille , int randPlacement) {
    int random = 0;
    random = 1 + rand() % ( taille - 2 );
    // Vérifier que la case choisie est vide (pas un mur)
    // Marquer la case de départ dans la matrice et la retourner
    switch (randPlacement) {
        case 2:
                while ( (*maze)[ random ][ 1 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ 0 ] = CHECKPOINT;
             
            break;
        case 3:
            while ( (*maze)[ taille - 2  ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ taille - 1 ][ random ] = CHECKPOINT;

            break;
        case 0:
                while ( (*maze)[ random ][ taille - 2 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ taille - 1 ] = CHECKPOINT;   
            break;
        case 1:
            while ( (*maze)[ 1 ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ 0 ][ random ] = CHECKPOINT;
            break;
        default:
            break;
    
    }
}

void mazePlacementComplexe(int*** maze, int taille, Joueur*j, int posMazeL,int posMazeC){
    if(!(posMazeC%2 || posMazeL%2)){
        // 0 / 0 --> 3 0
        // 2 / 2 --> 2 1
        // 0 / 2 --> 3 2
        // 2 / 0 --> 1 0
        switch (posMazeC+posMazeL) {
            case 0:
                setCheck(maze,taille,3);
                setCheck(maze,taille,0);
                break;
            case 2:
                if(posMazeL == 2){
                    setCheck(maze,taille,1);
                    setCheck(maze,taille,0);;

                }else{
                    setCheck(maze,taille,3);
                    setCheck(maze,taille,2);
                }
                break;
            case 4:
                setCheck(maze,taille,2);
                setCheck(maze,taille,1);
                break;
        }
 

    }else{
        if(posMazeL%2 && posMazeC%2){ //no 3
            for(int i=0;i<4;i++){
                setCheck(maze,taille,i);
            }
        }else{
            if(posMazeC == 2){
            setEnd(maze,taille,2);
            setCheck(maze,taille,1);
            setCheck(maze,taille,3);
            setCheck(maze,taille,2);
            }
            if(posMazeC == 0){
                setCheck(maze,taille,1);
                setCheck(maze,taille,3);
                setCheck(maze,taille,0);
                setStart(maze,taille,2,j);
            }
            if(posMazeC == 1){
                if(posMazeL == 2){
                    setCheck(maze,taille,1);
                    setCheck(maze,taille,0);
                    setCheck(maze,taille,2);
                }else{

                    setCheck(maze,taille,3);
                    setCheck(maze,taille,0);
                    setCheck(maze,taille,2);
                }
    
            
            }
        }
        
    }
}


void creerMegaMaze(Jeu* jeu){
    jeu->maze.sizeMaze = INITIALSIZE+(jeu->level);
    jeu->posMaze[0] = 1;
    jeu->posMaze[1] = 0;

    int size = 3;
    jeu->megamaze = (Maze**)malloc(size * sizeof(Maze*));
    for (int ligne = 0; ligne <  size; ligne++) {
        jeu->megamaze[ligne] = (Maze*)malloc(size * sizeof(Maze));
        for (int colonne= 0; colonne < size; colonne++) {
            mazeGenerator(&jeu->maze.tabMaze,jeu->maze.sizeMaze);
            mazePlacementComplexe(&jeu->maze.tabMaze,jeu->maze.sizeMaze,&jeu->j,ligne,colonne);
            jeu->maze.typeMaze = 0;
            jeu->megamaze[ligne][colonne] = jeu->maze;  // Initialiser la matrice avec des murs (-1)
        }
    }
}


void creerMaze(Jeu* jeu){

    jeu->maze.sizeMaze = jeu->maze.sizeMaze + jeu->level;
    mazeGenerator(&jeu->maze.tabMaze,jeu->maze.sizeMaze);
    mazePlacementSimple(&jeu->maze.tabMaze,jeu->maze.sizeMaze,&jeu->j);
    jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
    if(jeu->maze.typeMaze){
        jeu->maze.arbreCheminDepart = jeu->maze.arbreChemin;
        }
}

void placerEvents(Maze* maze,int level){
    for(int nbEvents = 0; nbEvents < level; nbEvents++){
        int lrandom = rand() % maze->sizeMaze;
        int crandom = rand() % maze->sizeMaze;
        do{
            lrandom = rand() % maze->sizeMaze;
            crandom = rand() % maze->sizeMaze;

        }while(maze->tabMaze[lrandom][crandom] != SPACE);
        maze->tabMaze[lrandom][crandom] = EVENT;
    }
}

void placerKeys(Maze* maze, Joueur* j){
        j->findKeys = 0;
        int lrandom = rand() % maze->sizeMaze;
        int crandom = rand() % maze->sizeMaze;
        do{
            lrandom = rand() % maze->sizeMaze;
            crandom = rand() % maze->sizeMaze;

        }while(maze->tabMaze[lrandom][crandom] != SPACE);
            maze->tabMaze[lrandom][crandom] = KEY;
}

void findCheck(Jeu* jeu,int positionInverse,int mode){
    int i = 1;
    // mode 1 --> recherche ligne sinon  0 --> recherche colonne
    afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji,jeu->options.typeMode);
    if(mode){
        while(jeu->maze.tabMaze[i][positionInverse] != CHECKPOINT && i < jeu->maze.sizeMaze){
            i++;
        }
        jeu->j.positions[0] = i;
        jeu->j.positions[1] = positionInverse;
    }else{
        while(jeu->maze.tabMaze[positionInverse][i] != CHECKPOINT && i < jeu->maze.sizeMaze){
            i++;
        }
        jeu->j.positions[0] = positionInverse;
        jeu->j.positions[1] = i;
    }
}

void verifCheck(Jeu* jeu, int** maze, int positionL, int positionC){
    if(positionL > -1 && positionC > -1 && positionC < jeu->maze.sizeMaze && positionL < jeu->maze.sizeMaze){
        if((maze[positionL][positionC]) == CHECKPOINT){
            jeu->j.etatCheckPoint = 0;
            jeu->maze.tabMaze[jeu->j.positions[0]][jeu->j.positions[1]] = SPACE; 
            if(positionC == 0){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]-1];
                jeu->posMaze[1]--;
                findCheck(jeu,jeu->maze.sizeMaze-1,1);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            }
            if(positionL == 0){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]-1][jeu->posMaze[1]];
                jeu->posMaze[0]--;

                findCheck(jeu,jeu->maze.sizeMaze-1,0);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            }
            if(positionC == (jeu->maze.sizeMaze-1)){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]+1];
                jeu->posMaze[1]++;
                afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji,jeu->options.typeMode);

                findCheck(jeu,0,1);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            
            }
            if(positionL == (jeu->maze.sizeMaze-1)){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]+1][jeu->posMaze[1]];
                jeu->posMaze[0]++;

                findCheck(jeu,0,0);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            
            }
        }
    }
}



