#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_MAX 100000 //obsolete ?
#define START_N 1
#define START_SIZE 10

typedef struct Microbes {
    int length_max;
    int taille;
    char **tab;
} Microbes;

int getLength(Microbes m) {
    return m.taille;
}

int getMaxLength(Microbes m) {
    return m.length_max;
}

void afficher(Microbes m) {
    int length = getLength(m);

    printf("Tableau de microbes: [");
    for (int i = 0; i < length; i++) {
        if (i != 0) { printf(", "); }
        printf("%s", m.tab[i]);
    }
    printf("]\n");
}

// return index max between both *numbers*
int my_strcmp(char *dest, char *src) {
    int length_dest = strlen(dest);
    int length_src = strlen(src);

    if (length_dest < length_src) {
        return 2;
    } else if (length_dest > length_src) {
        return 1;
    } else {
        for (int i = 0; i < length_dest; i++) {
            if (dest[i] < src[i]) {
                return 2;
            } else if (dest[i] > src[i]) {
                return 1;
            }
        }

        return 0;
    }
}

int sale(Microbes m, char *cmp, int index) {
    while (my_strcmp(m.tab[index], cmp) == 0
            || my_strcmp(m.tab[index], cmp) == 1) {
        index++;
    }

    return index;
}

int indexGreaterInf(Microbes m, int a, int b, char *cmp) {
    /*DICHOTOMIE*/
    int mid = (b + a) / 2;
    if (b - a == 1) {
        return mid;
    }

    switch (my_strcmp(m.tab[mid], cmp)) {
        case 0:
            return mid;
        case 1:
            return indexGreaterInf(m, mid, b, cmp);
        case 2:
            return indexGreaterInf(m, a, mid, cmp);
        default:
            return -1;
    }
}

char* createString(int length) {
    return (char*) malloc((length+1) * sizeof(char));
}

char* getInput(int size) {
    char c;
    char *str;
    int len = 0;
    str = malloc(sizeof(char) * size);

    scanf("%c", &c);
    while (c != ' ' && c != '\n') {
        str[len++] = c;
        if (len == size) {
            char *tmp = realloc(str, sizeof(char) * (size*=2));
            if (tmp == NULL) {
                exit(-3);
            } else {
                str = tmp;
            }
        }

        scanf("%c", &c);
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

void destroy(Microbes *m) {
    int length = m->taille;
    for (int i = 0; i < length; i++) {
        free(m->tab[i]);
    }
}

Microbes initMicrobes() {
    Microbes m;
    m.tab = (char**) malloc(START_N * sizeof(char*));
    if (m.tab == NULL) { exit(-4); }

    m.length_max = START_N;
    m.taille = 0;

    return m;
}

int main() {
    char *number_read;
    int index = 0;
    Microbes m = initMicrobes();

    number_read = getInput(START_SIZE);
    m.tab[m.taille] = createString(strlen(number_read));
    strcpy(m.tab[m.taille++], "0");

    if (!strcmp(number_read, "0")) {
        m.taille = 0;
    }

    while (strcmp(number_read, "0")) {
        if (my_strcmp(m.tab[m.taille - 1], number_read) == 1 ||
            my_strcmp(m.tab[m.taille - 1], number_read) == 0) {

            if (getLength(m) == getMaxLength(m)) {
                m.tab = realloc(m.tab, sizeof(char*) * (m.length_max*=2));
            }

            m.tab[m.taille] = createString(strlen(number_read));
            strcpy(m.tab[m.taille++], number_read);
        } else {
            index = indexGreaterInf(m, 0, m.taille, number_read);
            index = sale(m, number_read, index);
            if (index >= m.taille) {
                exit(-2);
            }

            strcpy(m.tab[index], number_read);
        }
        //afficher(m); //debug option
        number_read = getInput(START_SIZE);
    }

    free(number_read);
    destroy(&m);
    /* REPONSE A L'EXERCICE */
    printf("%d\n", getLength(m));

    return 0;
}
