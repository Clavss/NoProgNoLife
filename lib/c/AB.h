#ifndef AB_H
    #define AB_H
    #define element_t void*

    struct arbre {
        element_t donnee;
        struct arbre *droite; 
        struct arbre *gauche;
    };
    typedef struct arbre *AB;

    AB nouvelleAB(element_t donnee);
    AB nouveauNoeud(AB gauche,element_t donnee,AB droite);
    int estFeuille(AB ab);
    AB filsGauche(AB ab);
    AB filsDroit(AB ab);
    
#endif