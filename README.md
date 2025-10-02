# Cub3D

## Description
Cub3D est un projet de l'École 42 qui consiste à créer un moteur de rendu 3D inspiré du jeu Wolfenstein 3D. Le projet utilise la technique du raycasting pour créer un environnement 3D navigable en temps réel.

## Objectifs pédagogiques
- Comprendre les bases du rendu graphique 3D
- Maîtriser la technique du raycasting
- Manipuler des textures et des sprites
- Gérer les événements clavier et souris
- Optimiser les performances en temps réel

## Fonctionnalités
- **Rendu 3D** en temps réel avec raycasting
- **Déplacement fluide** du joueur (WASD)
- **Rotation de la caméra** avec les flèches directionnelles
- **Textures murales** différenciées selon l'orientation
- **Système de collision** avec les murs
- **Parsing de map** depuis un fichier .cub
- **Gestion des couleurs** pour le sol et le plafond

## Technologies utilisées
- **Langage** : C
- **Bibliothèque graphique** : MiniLibX
- **Système de build** : Makefile
- **Mathématiques** : Trigonométrie, géométrie vectorielle

## Prérequis
- GCC compiler
- MiniLibX library
- Make
- Système X11 (Linux) ou équivalent

## Installation et compilation

### 1. Cloner le projet
```bash
git clone <repository-url>
cd Cub3D
```

### 2. Compiler le projet
```bash
make
```

### 3. Nettoyer les fichiers objets
```bash
make clean    # Supprime les .o
make fclean   # Supprime tout + l'exécutable
make re       # Recompile tout
```

## Utilisation

### Lancement du jeu
```bash
./cub3D maps/map.cub
```

### Contrôles
- **W, A, S, D** : Déplacement
- **Flèches gauche/droite** : Rotation de la caméra
- **ESC** : Quitter le jeu

### Format de map (.cub)
```
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Structure du projet
```
Cub3D/
├── Makefile              # Compilation
├── includes/             # Headers (.h)
├── srcs/                # Code source
│   ├── main.c
│   ├── cast_ray/        # Algorithme de raycasting
│   ├── key_event/       # Gestion des événements
│   ├── parsing/         # Lecture et validation de la map
│   └── utils/           # Fonctions utilitaires
├── libft/               # Bibliothèque personnelle
├── mlx/                 # MiniLibX
├── map/                 # Fichiers de cartes
└── sprite/              # Textures et sprites
```

## Algorithme de raycasting
Le raycasting fonctionne en :
1. **Lance un rayon** pour chaque colonne de l'écran
2. **Calcule la distance** jusqu'au premier mur touché
3. **Détermine la hauteur** du mur à afficher
4. **Applique la texture** appropriée selon l'orientation

## Normes et contraintes 42
- Code conforme à la **Norme 42**
- Gestion stricte de la **mémoire** (pas de leaks)
- **Gestion d'erreurs** robuste
- Interdiction des **variables globales**
- Utilisation limitée des **fonctions autorisées**

## Compétences développées
- Programmation graphique en C
- Mathématiques appliquées (trigonométrie)
- Optimisation d'algorithmes
- Gestion mémoire rigoureuse
- Architecture logicielle

## Auteur
Alexandre Pommier (apommier) - École 42