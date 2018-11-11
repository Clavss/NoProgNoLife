#ifndef AB_H
    #define AB_H
    #define element_t void*

    struct arbre {
        element_t donnee;
        struct arbre *droite; 
        struct arbre *gauche;
    };
    typedef struct arbre *AB;

    AB nouvelAB(element_t);
    AB nouveauNoeud(AB, element_t, AB);
    int estFeuille(AB);
    AB filsGauche(AB);
    AB filsDroit(AB);
    
#endif