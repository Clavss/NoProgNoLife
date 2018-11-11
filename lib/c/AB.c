#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AB.h"
#include "file.h"

AB nouvelAB(element_t donnee){
    return nouveauNoeud(NULL, donnee, NULL);
}

AB nouveauNoeud(AB gauche, element_t donnee, AB droite) {
    AB ab = (AB) malloc(sizeof(struct arbre));
    ab->gauche = gauche;
    ab->donnee = donnee;
    ab->droite = droite;

    return ab;
}

int estFeuille(AB ab) {
    return (ab->gauche == NULL && ab->droite);
}

AB filsGauche(AB ab) {
    if (ab == NULL) {
        printf("Demande de fils gauche sur un arbre vide, erreur\n");
        return NULL;
    } else{
        return ab->gauche;
    }
}

AB filsDroit(AB ab) {
    if (ab == NULL) {
        printf("Demande de fils droit sur un arbre vide, erreur\n");
        return NULL;
    } else {
        return ab->droite;
    }
}

int nbNoeud(AB ab) {
    if (ab == NULL) { return 0; }

    return nbNoeud(filsGauche(ab)) + nbNoeud(filsDroit(ab)) + 1;
}

AB* parcourLargeur(AB a) {
    File f = nouvelleFile(a);
    AB* liste = malloc(sizeof(long int) * nbNoeud(a));
    int c = 0;

    while (!estVide(f)) {
        AB s = defiler(f);

        if (filsGauche(s) != NULL) {
            enfiler(f, filsGauche(s));
        }

        if (filsDroit(s) != NULL) {
            enfiler(f, filsDroit(s));
        }

        liste[c++] = s;
    }

    return liste;
}

/* EXEMPLE D'UTILISATION */
int main() {
    //créé un arbre avec 1 en racine, 2 en fils gauche et 3 en fils droit
    element_t test = malloc(sizeof(int));
    element_t test2 = malloc(sizeof(int));
    element_t test3 = malloc(sizeof(int));
    *(int*) test = 1;
    *(int*) test2 = 2;
    *(int*) test3 = 3;
    AB ab = nouveauNoeud(nouvelAB(test2), test, nouvelAB(test3));

    //parcours en largeur
    AB* sortie = parcourLargeur(ab);

    for (int i = 0; i < nbNoeud(ab); i++) {
        printf("%d\n", *(int*)sortie[i]->donnee);
    }

    return 0;
}
