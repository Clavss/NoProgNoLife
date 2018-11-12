#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file.h"

File nouvelleFile(element_t donnee) {
    File file = (File) malloc(sizeof(struct head_t));
    file->head = nouvelleCellule(donnee);
    file->tail = file->head;

    return file;
}

Element nouvelleCellule(element_t donnee) {
    Element e = (Element) malloc(sizeof(struct cellule_t));
    e->donnee = donnee;
    e->suivant = NULL;

    return e;
}

int estFileVide(File file) {
    assert(file != NULL);

    return (file->head == NULL);
}

void enfiler(File file, element_t donnee) {
    Element f = nouvelleCellule(donnee);

    if (estFileVide(file)) {
        file->head = file->tail = nouvelleCellule(donnee);
        return;
    }

    file->tail->suivant = f;
    file->tail = f;
}

element_t defiler(File file) {
    assert(!estFileVide(file));

    if (file->head == file->tail) {
        element_t retour = file->head->donnee;
        free(file->head);
        file->head = file->tail = NULL;
        return retour;
    }

    Element temp = file->head;
    element_t retour = temp->donnee;
    file->head = file->head->suivant;
    
    return retour;
}

void detruireFile(File file) {
    while (!estFileVide(file)) {
        defiler(file);
    }
    
    free(file);
}

/* EXEMPLE D'UTILISATION
int main() {
    File file = nouvelleFile(10);

    enfiler(file, 20);
    enfiler(file, 30);

    while(!estFileVide(file)) {
        printf("%d defiler\n", defiler(file));
    }

    enfiler(file, 30);
    detruireFile(file);

    return 0;
}
*/