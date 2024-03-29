#ifndef PILE_TABLEAU_H
    #define PILE_TABLEAU_H
    #define element_t int

    typedef struct {
        unsigned taille;
        element_t top; // top: indice max
        element_t *tableau;
    } Pile;

    Pile* creerPile(unsigned);
    int estPleine(Pile);
    int estPileVide(Pile);
    int push(Pile*, element_t);
    element_t pop(Pile*);
    element_t sommet(Pile);
    void detruirePile(Pile*);
#endif