#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH_NUMBER_MAX 1000000
#define N_MAX 1000000

int cnt(int microbes[], int n) {
    int nb = 0;

    for (int i = 0; i < n; i++) {
        if (microbes[i] != 0) {
            nb++;
        }
    }

    return nb;
}

void afficher(int microbes[], int n) {
    printf("Tableau de microbes: [");
    for (int i = 0; i < n; i++) {
        if (i != 0) { printf(", "); }
        printf("%d", microbes[i]);
    }
    printf("]\n");
}

int indexGreaterInf(int microbes[], int n, int cmp) {
    int max = 0;
    int indexMax = -1;

    for (int i = 0; i < n; i++) {
        if (microbes[i] < cmp && microbes[i] > max) {
            max = microbes[i];
            indexMax = i;
        }
    }

    return indexMax;
}

int main() {
    int cnt_microbe = 0;
    int microbes[N_MAX];
    int number_read;
    int index = -1;

    scanf(" %d", &number_read);
    while (number_read != 0) {
        index = indexGreaterInf(microbes, cnt_microbe, number_read);
        //printf("indexLowerSup(%d): [%d]\n", number_read, index);
        if (-1 != index) {
            microbes[index] = number_read;
        } else {
            microbes[cnt_microbe++] = number_read;
        }

        scanf(" %d", &number_read);
    }

     /* REPONSE A L'EXERCICE */
    printf("%d\n", cnt(microbes, cnt_microbe));
    //afficher(microbes, cnt_microbe);

    return 0;
}
