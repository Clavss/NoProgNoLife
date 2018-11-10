#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AB.h"
#include ""

AB nouvelleAB(element_t donnee){
    return nouveauNoeud(NULL,donnee,NULL);
}

AB nouveauNoeud(AB gauche,element_t donnee,AB droite){
     AB ab = (AB)malloc(sizeof(struct arbre));
     ab->gauche = gauche;
     ab->donnee = donnee;
     ab->droite = droite;
     return ab;
}

int estFeuille(AB ab){
    return (ab->gauche == NULL && ab->droite);
}

AB filsGauche(AB ab){
    if(ab == NULL){
        printf("Demande de fils gauche sur un arbre vide, erreur\n");
    }
    else{
        return ab->gauche;
    }
}

AB filsDroit(AB ab){
    if(ab == NULL){
        printf("Demande de fils droit sur un arbre vide, erreur\n");
    }
    else{
        return ab->droite;
    }
}

void afficherArbre(AB ab){
    
}



