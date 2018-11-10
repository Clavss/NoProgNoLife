#ifndef AB_H
    #define AB_H
    #define element_t int

    struct arbre {
        element_t donnee;
        struct arbre *droite; 
        struct arbre *gauche;
    };
    typedef struct arbre *AB;

    
#endif