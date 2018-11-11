#ifndef AB_H
    #define AB_H
    #define element_t int

    struct arbre {
        element_t donnee;
        struct arbre *droite; 
        struct arbre *gauche;
    };
    typedef struct arbre *AB;

    AB nouvelAB(element_t);
    AB nouveauNoeud(AB, element_t, AB);
    AB filsGauche(AB);
    AB filsDroit(AB);
    int estFeuille(AB);
    element_t getDonnee(AB);
    void parcourPrefixe(AB);
    void detruireArbre(AB);
#endif