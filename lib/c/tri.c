#include <stdio.h>
#include <stdlib.h>

int Partitionner(int tab[], int premier, int dernier, int pivot) {
    int temp;
    int j = premier;

    temp = tab[dernier];
    tab[dernier] = tab[pivot];
    tab[pivot] = temp;

    for (int i = premier; i < dernier; i++) {
        if (tab[i] <= tab[dernier]) {
            temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            j = j + 1;
        }
    }
    
    temp = tab[dernier];
    tab[dernier] = tab[j];
    tab[j] = temp;
    
    return j;
}

void tri_rapide(int tab[], int premier, int dernier) {
    int pivot;
    if (premier < dernier) {
        pivot = premier;
        pivot = Partitionner(tab, premier, dernier, pivot);
        tri_rapide(tab, premier, pivot-1);
        tri_rapide(tab, pivot+1, dernier);
    }
}

void tri(int tab[], int taille) {
    tri_rapide(tab, 0, taille-1);
}