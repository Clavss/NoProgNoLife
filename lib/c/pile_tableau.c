#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pile_tableau.h"

Pile* creerPile(unsigned taille) {
    Pile *pile = (Pile*) malloc(sizeof(Pile));
    pile->taille = taille;
    pile->top = -1;
    pile->tableau = (element_t*) malloc(pile->taille * sizeof(element_t));

    return pile;
}

int estPleine(Pile pile) {
    return pile.top == pile.taille - 1;
}

int estVide(Pile pile) {
    return pile.top == -1;
}

int push(Pile *pile, element_t element) {
    if (estPleine(*pile)) { return -1; }

    pile->tableau[++pile->top] = element;
    return 1;
}

element_t pop(Pile *pile) {
    assert(!estVide(*pile));

    return pile->tableau[pile->top--];
}

element_t sommet(Pile pile) {
    assert(!estVide(pile));

    return pile.tableau[pile.top];
}

void detruirePile(Pile *pile) {
    free(pile->tableau);
    free(pile);
}

/* EXEMPLE D'UTILISATION
int main() {
    Pile *pile = creerPile(100);

    push(pile, 10);
    push(pile, 20);

    printf("%d popped from stack\n", pop(pile));
    printf("Top element is %d\n", sommet(*pile)); 

    detruire(pile);

    return 0;
}
*/