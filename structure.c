#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bout bout;

typedef struct bout{
    int x;
    int y;
    bout* prec;
    bout* suiv;
    char forme[2]; 
} bout;


typedef struct {
    int taille;
    int direction;
    bout *premier;
    bout *dernier;   
} Liste;

typedef struct{
    int x;
    int y;
} pomme;


Liste* liste_init(){
    Liste *l = (Liste*)malloc(sizeof(Liste));
    if (l != NULL){
        l->premier=NULL;
        l->dernier=NULL;
        l->taille=0;
        l->direction = 2;
    }
    return l;
}

bout* creer_corps(int pos_x, int pos_y, char cara[]){
    bout* c= malloc(sizeof(bout));
    if(c!=NULL){
        c->x=pos_x;
        c->y=pos_y;
        c->suiv = NULL;
        c->prec = NULL;
        strcpy(c->forme,cara);
    }
    return c;
}

pomme* creer_pomme(int pos_x, int pos_y){
    pomme* c= malloc(sizeof(pomme));
    if(c!=NULL){
        c->x=pos_x;
        c->y=pos_y;
    }
    return c;
}

void avancer(Liste* liste){
    bout* c= liste->dernier;
    for(int i=0; i< (liste->taille) -1; i++){
        c->x = c->suiv->x;
        c->y = c->suiv->y;
        strcpy(c->forme,c->suiv->forme);
        c = c->suiv;
    }
    if(liste->direction == 1){
        liste->premier->x +=1;
        strcpy(liste->premier->forme,"─");
    }
    else if(liste->direction == 2){
        liste->premier->y +=1;
        strcpy(liste->premier->forme,"│");
    }
    else if(liste->direction == -1){
        liste->premier->x -=1;
        strcpy(liste->premier->forme,"─");
    }
    else if(liste->direction == -2){
        liste->premier->y -=1;
        strcpy(liste->premier->forme,"│");
    }
}

void manger(Liste* liste){
    bout* c = creer_corps(liste->dernier->x, liste->dernier->y, liste->dernier->forme);
    c ->suiv = liste->dernier;
    liste->dernier->prec = c;
    liste->taille+=1;
    liste->dernier = c;
    c = c->suiv;
    for(int i=0; i< (liste->taille) -2; i++){
        c->x = c->suiv->x;
        c->y = c->suiv->y;
        strcpy(c->forme,c->suiv->forme);
        c = c->suiv;
    }
    if(liste->direction == 1){
        liste->premier->x +=1;
        strcpy(liste->premier->forme,"─");
    }
    else if(liste->direction == 2){
        liste->premier->y +=1;
        strcpy(liste->premier->forme,"│");
    }
    else if(liste->direction == -1){
        liste->premier->x -=1;
        strcpy(liste->premier->forme,"─");
    }
    else if(liste->direction == -2){
        liste->premier->y -=1;
        strcpy(liste->premier->forme,"│");
    }
}



void initialisation(Liste* liste){
    liste->premier = creer_corps(25,12,"│");
    liste->dernier = creer_corps(25,11,"│");
    liste->dernier->suiv = liste->premier;
    liste->premier->prec= liste->dernier;
    liste->taille = 2;
}

void tour_snake(int direction, Liste* liste){
    if (abs(direction) != abs(liste->direction) ){
        if(liste->direction == 1){
            if(direction==-2){
                strcpy(liste->premier->forme,"┘");
            }
            else{
                strcpy(liste->premier->forme,"┐");
            }
        }
        else if(liste->direction == -1){
            if(direction==-2){
                strcpy(liste->premier->forme,"└");
            }
            else{
                strcpy(liste->premier->forme,"┌");
            }
        }
        else if(liste->direction == -2){
            if(direction==-1){
                strcpy(liste->premier->forme,"┐");
            }
            else{
                strcpy(liste->premier->forme,"┌");
            }
        }
        else if(liste->direction == 2){
            if(direction==-1){
                strcpy(liste->premier->forme,"┘");
            }
            else{
                strcpy(liste->premier->forme,"└");
            }
        }
        liste->direction = direction;
    }
}