#include "affichage.h"
#include "event.h"
#include "game.h"
#include "generation.h"

char** lireMenu(){        

    //allocation de la mémoire
    char** menus;
    menus = malloc(3*sizeof(char*));
    for (int i=0; i<3; i++){
        menus[i]=malloc(100*sizeof(char));
    }

    menus[0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║ "BWHT"▶ JOUER    ◀ "BGRN"║  ╔════════╣\n║  ╠══╗  ║  ║   OPTIONS    ║  ║  ════  ║\n║     ║  ║  ║   RÈGLES     ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    menus[1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   JOUER      ║  ╔════════╣\n║  ╠══╗  ║  ║ "BWHT"▶ OPTIONS  ◀"BGRN" ║  ║  ════  ║\n║     ║  ║  ║   RÈGLES     ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    menus[2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   JOUER      ║  ╔════════╣\n║  ╠══╗  ║  ║   OPTIONS    ║  ║  ════  ║\n║     ║  ║  ║ "BWHT"▶ RÈGLES   ◀"BGRN" ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    
    return menus;
}

void choixMenu(char** menus,Options* options){
    printf(BGRN);
    char*** optionsTab = NULL;
    initOptions(&optionsTab,options);

    int numMenu = 0;
    int jeuLance = 0;
    while (!jeuLance){
        system("clear");
        printf("%s", menus[numMenu]);
        switch (deplacementTouche(ETAT_MENU)) {
            case HAUT:
                numMenu--;
                if(numMenu==-1){
                    numMenu=2;
                }
                break;
            case BAS:
                numMenu++;
                if(numMenu==3){
                    numMenu=0;
                }
                break;
            case ENTER:
                switch (numMenu) {
                    case 0:
                        jeuLance = 1;
                        break;
                    case 1:
                        optionChange(options,optionsTab);
                        break;
                    case 2:
                        regle(options);
                        break;
                }
                // jeuLance=1;
                break;

            default:
                break;
        }        
        //return numMenu;
        //renvoie 0 pour jouer, 1 pour options et 2 pour règles
    }
    printf(reset);
    // for (int i=0; i<3; i++){
    //     free(menus[i]);
    // }
    // free(menus);

    // for (int i=0; i<3; i++){
    //     for (int j=0; j<4; j++){
    //     free(optionsTab[i][j]);
    //     }
    //     free(optionsTab[i]);
    // }
    // free(optionsTab);
}

void regle(Options* options){
    int lecture=0;
    while(!lecture){
        system("clear");
        printf("\n ""\e[4;33m""Le Labyrinthe :");
        printf("\n\n""\e[0m""\e[1;97m"" Le jeu est plutôt simple et facile à comprendre.\n Il suffit de déplacer le personnage jusqu'à l'arrivée 🏁.\n\n""\e[1;32m"" Les déplacements sont réalisés en utilisant :\n - Z pour aller vers le haut ➡️ \n - Q pour aller vers la gauche ➡️\n - S pour aller vers le bas ⬇️\n - D pour aller vers la droite ➡️\n\n Sur votre route, vous aurez la possibilité de récupérer des bonus ou des malus : \n - Touches numériques 1️⃣ /2️⃣ /3️⃣ /4️⃣ /5️⃣  pour utiliser l'item depuis votre inventaire\n\n ""\e[4;37m""Leurs effets sont les suivants :""\e[0m""\e[1;37m""\n\n - Pièce d'or 🪙 : bonus de points de score\n - Médicament 💊 : soigne 2 ❤️\n - Ambulance 🚑 : soigne 5 ❤️\n - Chute de pierres 🤕 : perte de 2 ❤️\n - Piège à flammes 🔥 : perte de ❤️  sur la durée\n - Poison 🧪 : perte plus intense de ❤️  sur la durée\n - Champagne 🍾 : perturbe la vision et l'estimation des distances, augmente la sensibilité à l'éblouissement, altère la coordination des mouvements. (à consommer avec modération)\n - Lait 🥛 : annule les effets du poison, du champagne et même du feu ! (à consommer sans modération)\n - Fil d'Ariane 🧶 : indique la sortie du labyrinthe, si elle est accessible.\n\n ""\e[4;37m""Modes de jeu :""\e[0m""\e[1;37m""\n Les modes EASY, NORMAL et HARD influent sur la vie de départ du joueur.\n À vous de découvrir les secrets des autres modes...\n\n Notes pour le mode ""\e[1;93m""Player""\e[1;97m"" :\n - Le champagne 🍾 diminue le champ de vision du joueur, jusqu'à être guéri par un verre de lait 🥛.\n - Le saxophone 🎷 augmente le champ de vision du joueur.\n\n\n""\e[3;37m"" Ce jeu a été realisé par Paul Brechenmacher, Paul Le Blanc, Etienne Massonnet et Gabin Alquier pour un projet de fin de premier semestre 2023-2024.");
        printf("\n\n    Pour quitter et lancer le jeu, appuyez sur 'Entrée'""\e[0m	");
        printf("\e[3;95m""\n\n\n\n\n\n\n\n    Un aventurier maquillé\n      Maniant un instrument cuivré\n        Dans le dédale embrumé il ose s'aventurer,\n        D'un club légendaire il souhaite percer les secrets\n"reset);
        switch(deplacementTouche(ETAT_ENTER)){
            case ENTER:
                lecture=1;
                break;
        }

    }
    choixMenu(lireMenu(),options);
}



void lireArsenal(){

FILE* arsenal = NULL;
    int** tab;
    int c;
    int l=0;
    char* temp;
    char ligne[1000];
    arsenal = fopen("./out/arsenal.csv", "r");
    if (arsenal == NULL){
        printf("Erreur d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }
    allouerTab2(&tab, 200);
    while(fgets(ligne,1000,arsenal) != NULL){
      temp=strtok(ligne," ");
      c=0;
      while(temp!=NULL){
        tab[l][c]=atoi(temp);
        temp=strtok(NULL, " ");
        c++;
      }
      l++;
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
          switch (tab[i][j]) {
                case SPACE:
                    printf("  "); // Espace vide
                    break;
                case WALL:
                    printf("🧱"); // Mur//Mur invisible
                    break;
                case END:
                    printf("🏁"); //Point d'arrivée
                    break;
                case WHITE:
                    printf("⬜");
                    break;
                case BLUE:
                    printf("🟦");
                    break;
            }
        }  
        printf("\n");
    }
    
    for(int i=0; i<200; i++){
        free(tab[i]);
    }
    free(tab);
    fclose(arsenal);

}



void afficherArbreChemins(arbreChemins a, int** maze){
    printf("[%d - %d] --> %d\n",a->positions[0],a->positions[1],a->type);
    for(int n = 0; n < a->nbFils; n++){
        afficherArbreChemins(a->fils[n],maze);
    }
}

char* emoji(int type){
    switch (type) {
        case NONE:
            return " - ";
        case HEALTH:
            return "💊 ";
        case MEDIKIT:
            return "🚑 ";
        case DAMAGE:
            return "🤕 ";
        case FIRE:
            return "🔥 ";
        case DRUNK:
            return "🍾 ";
        case MILK:
            return "🥛 ";
        case ARIANE:
            return "🧶 ";
        case POISON: 
            return "🧪 ";
        case SCORE:
            return "🪙 ";
        case FUN: 
            return "🎷 ";
        case KEY_ITEM:
            return "🗝️ ";
        default:
            return "Error";
    }
}

void afficherUseItem(int type){
    printf("╔═══════════════════════╗\n");
    printf("║ Vous avez trouvé %s  ║\n",emoji(type));
    printf("╚═══════════════════════╝\n");
}


int lenInt(int score){
    int len = 0;
    if (score == 0){
        len = 1;
    }
    while(score != 0){
        score = score/10;
        len++;
    }
    return len;
}

void scorePrint(int scoreLen){
    while(scoreLen < 5){
        printf(" ");
        scoreLen++;
    }
    printf("    ║\n");
}
void afficherScore(int level,int score){
printf("\e[1;97m");
printf("╔══════════════╗    ╔══════════════╗\n");
if(lenInt((level/2)+1)==2){
    printf("║  ""\e[1;92m""Niveau %d""\e[1;97m""   ║    ║  ""\e[1;33m""%d 🪙""\e[1;97m",(level/2)+1,score);
}else{
    printf("║   ""\e[1;92m""Niveau %d""\e[1;97m""   ║    ║  ""\e[1;33m""%d 🪙""\e[1;97m",(level/2)+1,score);
}
scorePrint(lenInt(score));
printf("╚══════════════╝    ╚══════════════╝\n");
printf(reset);
}

char* afficherKey(int findKey,int typeMaze){
    if(findKey && !typeMaze ){
        return emoji(KEY_ITEM);
    }else{
        return " ";
    }
}

void afficherInventaire(Jeu jeu){
printf("\e[1;97m");
printf("╔═1═╦═2═╦═3═╦═4═╦═5═╗\n");
printf("║%s║%s║%s║%s║%s║  %d❤️  %s\n",emoji(jeu.j.inventaire[0].type),emoji(jeu.j.inventaire[1].type),emoji(jeu.j.inventaire[2].type),emoji(jeu.j.inventaire[3].type),emoji(jeu.j.inventaire[4].type),jeu.j.pvHealth,afficherKey(jeu.j.findKeys,jeu.maze.typeMaze));
printf("╚═══╩═══╩═══╩═══╩═══╝\n");
printf(reset);
}

void afficherAroundPlayer(int** matrice , int n, int typeEmoji,int typeMode,Joueur joueur,int visionRange){
    for(int l = joueur.positions[0]-visionRange;l < joueur.positions[0]+visionRange+1 ;l++){
        for(int c = joueur.positions[1]-visionRange; c < joueur.positions[1]+visionRange+1; c++){
           if(l < 0 || c < 0 || c >= n ||l >= n){
                printf("  ");
           }else{
                switch (matrice[l][c]) {
                case SPACE:
                    printf("  "); // Espace vide
                    break;
                case WALL:
                    printf("🧱"); // Mur
                    break;
                case PLAYER:
                    afficherJoueur(typeEmoji);
                    break;
                case END:
                    printf("🏁"); //Point d'arrivée
                    break;
                case EVENT:
                    printf("❔");
                    break;
                case KEY:
                    printf("🗝️ ");
                    break;
                case CHECKPOINT:
                    printf("🚩");
                    break;
                case FIL:
                    printf("🔹");
                    break;
                default:
                    break; 
            }
           }
        }
        printf("\n");
    }
}

void optionChange(Options* options,char*** optionsTab){
    int lecture=0;
    int numOptions = 0;
    int numId = 0;

    while(!lecture){
        printf(reset);
        system("clear");
        printf(BPUR);
        printf("%s",optionsTab[numOptions][numId]);
        saveOptions(options,numOptions,numId);
        switch (deplacementTouche(ETAT_OPTION)) {
            case HAUT:
                numOptions--;
                if(numOptions==-1){
                    numOptions=2;
                }
                numId = getOptions(options,numOptions);
                break;
            case BAS:
                numOptions++;
                if(numOptions==3){
                    numOptions=0;
                }
                numId = getOptions(options,numOptions);
                break;
            case DROITE:
                numId++;
                if(numId==5){
                    numId=0;
                }
                break;
            case GAUCHE:
                numId--;
                if(numId==-1){
                    numId=4;
                }
                break;
            case ENTER:
                lecture=1;
                break;
        }
        printf(BGRN);
        // choixMenu(lireMenu());
}
}

void afficherJoueur(int typeEmoji){
    switch (typeEmoji) {
        case 0:
            printf("👾"); // Joueur
            break;
        case 1:
            printf("🤡"); // Joueur
            break;
        case 2:
            printf("💎"); // Joueur
            break;
        case 3:
            printf("👽");
            break;
        case 4:
            printf("⚽");
            break;
    }
}


void afficherMatrice1(int** matrice , int n, int typeEmoji,int typeMode) {
   // Afficher la matrice avec des symboles correspondant aux éléments
   for(int i = 0; i < n; i++){
        for(int j =0; j < n; j++){
            switch (matrice[i][j]) {
                case SPACE:
                    printf("  "); // Espace vide
                    break;
                case WALL:
                    if(typeMode != 3){
                        printf("🧱"); // Mur
                    }else{
                        printf("  "); //Mur invisible
                    }
                    break;
                case PLAYER:
                    afficherJoueur(typeEmoji);
                    break;
                case END:
                    printf("🏁"); //Point d'arrivée
                    break;
                case EVENT:
                    printf("❔");
                    break;
                case KEY:
                    printf("🗝️");
                    break;
                case CHECKPOINT:
                    printf("🚩");
                    break;
                case FIL:
                    printf("🔹");
                    break;
                case WHITE:
                    printf("⬜");
                    break;
                case BLUE:
                    printf("🟦");
                    break;
                default:
                    break; 
            }

        }
        printf("\n");
    }
}