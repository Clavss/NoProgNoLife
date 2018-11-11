#ifndef FILE_H
    #define FILE_H
    #define element_t void*

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
    int estVide(File);
    void enfiler(File, element_t);
    element_t defiler(File);
#endif