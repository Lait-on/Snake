#ifndef SNAKE_H
#define SNAKE_H

// Définition de la structure pour un segment du corps du serpent
typedef struct bout {
    int x; // Position en x
    int y; // Position en y
    struct bout *prec; // Pointeur vers le segment précédent
    struct bout *suiv; // Pointeur vers le segment suivant
    char forme[2]; // Forme du segment (ex: "│")
} bout;

// Définition de la structure pour une liste de segments formant le serpent
typedef struct {
    int taille; // Nombre de segments dans le serpent
    int direction; // Direction actuelle du serpent
    bout *premier; // Pointeur vers le premier segment
    bout *dernier; // Pointeur vers le dernier segment
} Liste;

// Définition de la structure pour une pomme
typedef struct {
    int x; // Position en x
    int y; // Position en y
} pomme;

// Fonction pour initialiser une liste de segments
Liste* liste_init();

// Fonction pour créer un segment du corps du serpent
bout* creer_corps(int pos_x, int pos_y, char cara[]);

// Fonction pour créer une pomme
pomme* creer_pomme(int pos_x, int pos_y);

// Fonction pour faire avancer le serpent dans la direction actuelle
void avancer(Liste* liste);

// Fonction pour faire manger le serpent (ajouter un segment à son corps)
void manger(Liste* liste);

// Fonction pour initialiser le serpent avec une taille et une position de départ
void initialisation(Liste* liste);

void tour_snake(int direction, Liste* liste);

#endif /* SNAKE_H */
