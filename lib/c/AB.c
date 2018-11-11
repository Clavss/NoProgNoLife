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

element_t getDonnee(AB ab) {
    assert(ab != NULL);

    return ab->donnee;
}

int nbNoeud(AB ab) {
    if (ab == NULL) { return 0; }

    return nbNoeud(filsGauche(ab)) + nbNoeud(filsDroit(ab)) + 1;
}

void parcourPrefixe(AB a) {
    printf("%d\n", getDonnee(a));

    AB fg = filsGauche(a);
    if (fg != NULL) {
        parcourPrefixe(fg);
    }

    AB fd = filsDroit(a);
    if (fd != NULL) {
        parcourPrefixe(fd);
    }
}

void detruireArbre(AB a) {
    AB fg = filsGauche(a);
    if (fg != NULL) {
        detruireArbre(fg);
    }

    AB fd = filsDroit(a);
    if (fd != NULL) {
        detruireArbre(fd);
    }

    free(a);
}

/* EXEMPLE D'UTILISATION
int main() {
    //créé un arbre avec 1 en racine, 2 en fils gauche et 3 en fils droit
    element_t test1 = 1;
    element_t test2 = 2;
    element_t test3 = 3;
    AB ab = nouveauNoeud(nouvelAB(test2), test1, nouvelAB(test3));

    parcourPrefixe(ab);

    detruireArbre(ab);

    return 0;
}
*/