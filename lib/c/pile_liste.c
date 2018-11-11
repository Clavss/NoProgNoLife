#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pile_liste.h"

Pile nouvelleCellule(element_t donnee) {
    Pile pile = (Pile) malloc(sizeof(struct cellule_t));
    pile->donnee = donnee;
    pile->suivant = NULL;

    return pile;
}

void push(Pile *pile, element_t donnee) {
    Pile new_pile = nouvelleCellule(donnee);
    new_pile->suivant = *pile;
    *pile = new_pile;
}

int estPileVide(Pile pile) {
    return (pile == NULL);
}

element_t pop(Pile *pile) {
    assert(!estPileVide(*pile));

    Pile temp = *pile;
    *pile = (*pile)->suivant;
    element_t res = temp->donnee;
    free(temp);

    return res;
}

element_t sommet(Pile pile) {
    assert(!estPileVide(pile));

    return pile->donnee;
}

void detruirePile(Pile *pile) {
    while (!estPileVide(*pile)) {
        pop(pile);
    }
}

/* EXEMPLE D'UTILISATION
int main() {
    Pile pile = NULL;

    push(&pile, 20);
    push(&pile, 30);

    printf("%d popped from stack\n", pop(&pile));
    printf("Top element is %d\n", sommet(pile));

    detruirePile(&pile);

    return 0;
}
*/