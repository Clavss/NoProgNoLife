#ifndef FILE_H
    #define FILE_H
    #define element_t int

    struct cellule_t {
        element_t donnee;
        struct cellule_t *suivant; 
    };
    typedef struct cellule_t *Element;

    struct head_t {
        Element head;
        Element tail;  
    };
    typedef struct head_t *File;
    
    File nouvelleFile(element_t);
    Element nouvelleCellule(element_t);
    int estFileVide(File);
    void enfiler(File, element_t);
    element_t defiler(File);
    void detruireFile(File);
#endif