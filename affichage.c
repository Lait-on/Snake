#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include <termios.h>
#include <sys/select.h>



void affichage_vide(){
    printf("\033[0;0H"); 
    printf("\033[2J"); 
    printf("┌────────────────────────────────────────────────┐\n");
    printf("│                                                │\n");
    printf("│                     ǝʞɐus                      │\n");
    printf("│                                                │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │          ┌────────────┐\n");
    printf("│                                                ├──────────┤score :     │\n");
    printf("│                                                │          └────────────┘\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
    
}



void affichage_serpent(Liste* liste){
    bout* c= liste->dernier;
    for(int i=0;i<liste->taille;i++){
        printf("\033[%d;%dH%s", c->y, c->x, c->forme);
        c = c->suiv;
    }
    printf("\033[22;1H");
    fflush(stdout);
    usleep(100000);

    c= liste->dernier;
    for(int i=0;i<liste->taille;i++){
        printf("\033[%d;%dH ", c->y, c->x);
    }
    printf("\033[22;1H");
}

void affichage_pomme(pomme* p){
    printf("\033[%d;%dH\033[0;31m♫\033[0m", p->y, p->x);
}

void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void test_sortie(Liste* liste, int *condition){
    if(liste->premier->x > 49 || liste->premier->x < 2 || liste->premier->y > 19 || liste->premier->y <6 ){
        *condition =0;
    }
    bout* p= liste->dernier;
    for (int i=0;i<liste->taille-2;i++){
        if (p->x == liste->premier->x && p->y == liste->premier->y){
            *condition =0;
            return;
        }
        p=p->suiv;
    }
}

int test_pomme(Liste* liste, pomme* p, int* score){
    if (liste->premier->x == p->x && liste->premier->y == p->y){
        *score +=1;
        return 1;
    }
    return 0;
}
void affichage_score(int score){
    char score_str[4]; // Un caractère pour le score et un pour le caractère nul
    snprintf(score_str, sizeof(score_str), "%03d", score);
    printf("\033[12;69H%s", score_str);
}

void animation_mort(Liste* liste){
    int pos_x = liste->premier->x, pos_y = liste->premier->y;
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    printf("\033[38;2;%d;%d;%dm\033[%d;%dH┌─┐",r,g,b,pos_y-1, pos_x-1);
    printf("\033[%d;%dH│", pos_y, pos_x-1);
    printf("\033[%d;%dH│",pos_y, pos_x+1);
    printf("\033[%d;%dH└─┘\033[0m", pos_y+1, pos_x-1);
    printf("\033[22;1H");
    fflush(stdout);
    usleep(500000);
    affichage_serpent(liste);
    printf("\033[38;2;%d;%d;%dm\033[%d;%dH┌   ┐",r,g,b,pos_y-1, pos_x -2);
    printf("\033[%d;%dH│  ", pos_y, pos_x-3);
    printf("\033[%d;%dH  │",pos_y, pos_x+1);
    printf("\033[%d;%dH└   ┘", pos_y+1, pos_x-2);
    printf("\033[%d;%dH─",pos_y+2,pos_x);
    printf("\033[%d;%dH─\033[0m",pos_y-2,pos_x);
    affichage_serpent(liste);
    printf("\033[22;1H");
    fflush(stdout);
    usleep(500000);
    printf("\033[38;2;%d;%d;%dm\033[%d;%dH     ",r,g,b,pos_y-1, pos_x -2);
    printf("\033[%d;%dH ", pos_y, pos_x-3);
    printf("\033[%d;%dH ",pos_y, pos_x+3);
    printf("\033[%d;%dH     ", pos_y+1, pos_x-2);
    printf("\033[%d;%dH ",pos_y+2,pos_x);
    printf("\033[%d;%dH \033[0m",pos_y-2,pos_x);
    
    printf("\033[38;2;%d;%d;%dm\033[%d;%dH┌─   ─┐",r,g,b,pos_y-2, pos_x -3);
    printf("\033[%d;%dH│  ", pos_y, pos_x-5);

    printf("\033[%d;%dH  │",pos_y, pos_x+3);

    printf("\033[%d;%dH└─   ─┘", pos_y+2, pos_x-3);
    printf("\033[%d;%dH─",pos_y+3,pos_x);
    printf("\033[%d;%dH─\033[0m",pos_y-3,pos_x);
    affichage_serpent(liste);
    fflush(stdout);
    usleep(500000);
}

void affichage_manger(Liste* liste){
    for(int i=0; i< 15; i++){
        int x= 2 + (rand()%48);
        int y= 2 + (rand()%3);
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        printf("\033[38;2;%d;%d;%dm\033[%d;%dH✶\033[0m",r,g,b,y,x);
    }
    
    
    fflush(stdout);

}

void process_arrow_key(char arrow, Liste* liste, int* condition) {
    switch (arrow) {
        case 'A':
            tour_snake(-2,liste);
            avancer(liste);
            test_sortie(liste, condition);
            if (*condition ==0){
                animation_mort(liste);
                break;}
            affichage_serpent(liste);
            break;
        case 'B':
            tour_snake(2,liste);
            avancer(liste);
            test_sortie(liste, condition);
            if (*condition ==0){
                animation_mort(liste);
                break;}
            affichage_serpent(liste);
            break;
        case 'C':
            tour_snake(1,liste);
            avancer(liste);
            test_sortie(liste, condition);
            if (*condition ==0){
                animation_mort(liste);
                break;}
            affichage_serpent(liste);
            break;
        case 'D':
            tour_snake(-1,liste);
            avancer(liste);
            test_sortie(liste, condition);
            if (*condition ==0){
                animation_mort(liste);
                break;}
            affichage_serpent(liste);
            break;
        default:
            printf("Autre séquence d'échappement\n");
            break;
    }
}

int main(){
    affichage_vide();
    Liste* liste= liste_init();
    initialisation(liste);
    int score=0;
    srand(time(NULL));
    int condition = 1;
    char last_key_pressed = '\0';   

    pomme* p = creer_pomme((2+rand()%48),(6+rand()%14));
    affichage_pomme(p);
    affichage_score(score);
    int miam=0;
    
    
   // Sauvegarde des paramètres du terminal actuel
struct termios original_termios;
tcgetattr(STDIN_FILENO, &original_termios);

// Modification des paramètres pour activer le mode non-canonique et non-bloquant
struct termios new_termios = original_termios;
new_termios.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'écho
new_termios.c_cc[VMIN] = 0;
new_termios.c_cc[VTIME] = 0;
tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

// Boucle principale
while (condition) {
    if (miam==1){
        affichage_vide();
        affichage_score(score);
        affichage_serpent(liste);
        affichage_pomme(p);
        miam =0;
    }
    else if(miam>1){
        miam-=1;
    }
    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100 ms

    int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);
    if (rv == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (rv > 0) {
        if (FD_ISSET(STDIN_FILENO, &set)) {
            char c;
            ssize_t num_read = read(STDIN_FILENO, &c, 1);
            if (num_read == 1) {
                if (last_key_pressed != '\0') {
                        flush_input(); // Reset de la pile de touches
                    }
                    last_key_pressed = c;
                if (c == '\033') {// Vérifie si le caractère est une séquence d'échappement
                        // Lit le prochain caractère pour détecter la flèche
                        char arrow;
                        if (read(STDIN_FILENO, &arrow, 1) == 1) {
                            if (arrow == '[') {
                                if (read(STDIN_FILENO, &arrow, 1) == 1) {
                                    process_arrow_key(arrow, liste, &condition); // Traite la flèche détectée
                                }
                            }
                        }
                }
                else if(c == 'z' || c == 'q' || c == 's' || c == 'd'){
                    if (c == 'z') {
                        tour_snake(-2,liste);
                        avancer(liste);
                        test_sortie(liste, &condition);
                        if (condition ==0){
                            animation_mort(liste);
                            break;}
                        affichage_serpent(liste);
                    }
                    else if(c== 'q'){
                        tour_snake(-1,liste);
                        avancer(liste);
                        test_sortie(liste, &condition);
                        if (condition ==0){
                            animation_mort(liste);
                            break;}
                        affichage_serpent(liste);
                    }
                    else if(c== 's'){
                        tour_snake(2,liste);
                        avancer(liste);
                        test_sortie(liste, &condition);
                        if (condition ==0){
                            animation_mort(liste);
                            break;}
                        affichage_serpent(liste);
                    }
                    else if(c== 'd'){
                        tour_snake(1,liste);
                        avancer(liste);
                        test_sortie(liste, &condition);
                        if (condition ==0){
                            animation_mort(liste);
                            break;}
                        affichage_serpent(liste);
                    }
                }
                
                
            }
        }
    } else {
        avancer(liste);
        test_sortie(liste, &condition);
        if (condition ==0){
            animation_mort(liste);
            break;}
        affichage_serpent(liste);
    }
    if (test_pomme(liste, p, &score)==1){
        p->x = (2+rand()%48);
        p->y = (6+rand()%14);
        miam=5;
        affichage_score(score);
        affichage_pomme(p);
        
        manger(liste);
        affichage_serpent(liste);
        affichage_manger(liste);
    }
    printf("\033[99;99H");
}

// Restauration des paramètres du terminal
printf("\033[100;100H");
tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);



}
