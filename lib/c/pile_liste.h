#ifndef PILE_LISTE_H
    #define PILE_LISTE_H
    #define element_t void*

    struct cellule_t {
        element_t donnee;
        struct cellule_t *suivant; 
    };
    typedef struct cellule_t *Pile;

    Pile nouvelleCellule(element_t);
    void push(Pile*, element_t);
    int estVide(Pile);
    element_t pop(Pile*);
    element_t sommet(Pile);
    void detruire(Pile*);
#endif