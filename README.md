# mazeProject
Programme en C d'un labyrinthe dans le terminal.

 ## Règle et Description du jeu

  
 Pour plus d'information sur la documentation : 
    https://nehkowp.github.io/mazeDoxygen/index.html
 
 Le jeu est plutôt simple et facile à comprendre.
 Il suffit de déplacer le personnage jusqu'à l'arrivée 🏁.

 Les déplacements sont réalisés en utilisant :
 - Z pour aller vers le haut ➡️
 - Q pour aller vers la gauche ➡️
 - S pour aller vers le bas ⬇️
 - D pour aller vers la droite ➡️

 Sur votre route, vous aurez la possibilité de récupérer des bonus ou des malus :
 - Touches numériques 1️⃣ /2️⃣ /3️⃣ /4️⃣ /5️⃣  pour utiliser l'item depuis votre inventaire

 Leurs effets sont les suivants :

 - Pièce d'or 🪙 : bonus de points de score
 - Médicament 💊 : soigne 2 ❤️
 - Ambulance 🚑 : soigne 5 ❤️
 - Chute de pierres 🤕 : perte de 2 ❤️
 - Piège à flammes 🔥 : perte de ❤️  sur la durée
 - Poison 🧪 : perte plus intense de ❤️  sur la durée
 - Champagne 🍾 : perturbe la vision et l'estimation des distances, augmente la sensibilité à l'éblouissement, altère la coordination des mouvements. (à consommer avec modération)
 - Lait 🥛 : annule les effets du poison, du champagne et même du feu ! (à consommer sans modération)
 - Fil d'Ariane 🧶 : indique la sortie du labyrinthe, si elle est accessible.

 Modes de jeu :
 Les modes EASY, NORMAL et HARD influent sur la vie de départ du joueur.
 À vous de découvrir les secrets des autres modes...

 Notes pour le mode Player :
 - Le champagne 🍾 diminue le champ de vision du joueur, jusqu'à être guéri par un verre de lait 🥛.
 - Le saxophone 🎷 augmente le champ de vision du joueur.

## Utilisation

Tous les terminaux n'affichent pas toujours les caractères de la même façon, voici les terminaux conseillés pour executer ce programme.
- Le terminal intégré de VSCode / VSCodium
- Le gnome-terminal de Ubuntu

```bash
git clone https://github.com/P33TheWhite/mazeProject.git
cd mazeProject
make
./exe
```

## Membres

 Ce jeu a été realisé par Gabin Alquier, Paul Brechenmacher, Etienne Massonnet et Paul Le Blanc pour un projet de fin de premier semestre 2023-2024.

 
 [Paul Brechenmacher](https://github.com/nehkowp)
 
 N'hésitez pas à aller voir ces projets. ")


### Easter egg
    Un aventurier maquillé
      Maniant un instrument cuivré
        Dans le dédale embrumé il ose s'aventurer,
        D'un club légendaire il souhaite percer les secrets
