#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Dico {
    int taille;
    char **tab;
    int *tabInd;
} Dico;

Dico initDico(int taille_mot_max, int nombre_mot_dico) {
    Dico d;
    d.tab = (char**) malloc(nombre_mot_dico * sizeof(char*));
    if (d.tab == NULL) {  printf("Malloc failure\n"); exit(-5); }
    d.taille = 0;

    for (int i = 0; i < nombre_mot_dico; i++) {
        d.tab[i] = (char*) malloc((taille_mot_max+1) * sizeof(char));
    }

    d.tabInd = (int*) malloc(sizeof(int) * nombre_mot_dico);

    return d;
}

Dico *initOccu(int taille_mot_max, int nombre_mot_dico, int nombre_lettre) {
    Dico *occu = (Dico*) malloc(sizeof(Dico) * nombre_lettre);
    for (int i = 0; i < nombre_lettre; i++) {
        occu[i] = initDico(taille_mot_max, nombre_mot_dico);
    }

    return occu;
}

void afficherDico(char *str, Dico d) {
    printf("%s: [", str);
    int length = d.taille;
    for (int i = 0; i < length; i++) {
        if (i != 0) { printf(", "); }
        printf("%s", d.tab[i]);
    }
    printf("]\n");
}

void afficherOccuTab(char **str, int taille, int* tabInd) {
    for (int i = 0; i < taille; i++) {
        printf("{%s -> dico[%d]} ", str[i], tabInd[i]);
    }
    printf("\n");
}

void afficherOccu(Dico *occu, int nombre_lettre) {
    for (int i = 0; i < nombre_lettre; i++) {
        printf("%c: %d : ", 'a'+i, occu[i].taille);
        afficherOccuTab(occu[i].tab, occu[i].taille, occu[i].tabInd);
    }
}

int appartient(char c, char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (c == str[i]) {
            return 1;
        }
    }

    return 0;
}

void getOccu(Dico dico, int nombre_lettre, Dico *occu) {
    for (int i = 0; i < nombre_lettre; i++) {
        if (occu[i].taille != -1) {
            occu[i].taille = 0;

            for (int y = 0; y < dico.taille; y++){
                if (appartient(i + 'a', dico.tab[y])) {
                    occu[i].tabInd[occu[i].taille] = y;
                    strcpy(occu[i].tab[occu[i].taille++], dico.tab[y]);
                }
            }
        }
    }
}

int checkImpossible(Dico *occu, int nombre_lettre) {
    for (int i = 0; i < nombre_lettre; i++) {
        if (occu[i].taille == 0) {
            return 1;
        }
    }
    return 0;
}

//met l'element à la fin et diminue la taille de 1
void popDico(int indice, Dico *dico, int taille_mot_max, Dico *occu, int nombre_lettre) {
    //swap
    if (indice != dico->taille-1) {
        char *tmp = (char*) malloc(sizeof(char) * (taille_mot_max+1));
        strcpy(tmp, dico->tab[indice]);
        strcpy(dico->tab[indice], dico->tab[dico->taille-1]);
        strcpy(dico->tab[dico->taille-1], tmp);
        free(tmp);
    }
    dico->taille--;

    getOccu(*dico, nombre_lettre, occu);
}

void checkLettreTrouve(char *str, Dico *occu) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        occu[str[i]-'a'].taille = -1;
    }
}

void push(char *str, Dico *res) {
    strcpy(res->tab[res->taille++], str);
}

int getMotForce(Dico *occu, int nombre_lettre) {
    for (int i = 0; i < nombre_lettre; i++) {
        if (occu[i].taille == 1) {
            return occu[i].tabInd[0];
        }
    }
    return -1;
}

int minTab(Dico *occu, int nombre_lettre) {
    int min = INT_MAX;
    for (int i = 0; i < nombre_lettre; i++) {
        if (occu[i].taille < min && occu[i].taille != -1) {
            min = occu[i].taille;
        }
    }

    return min;
}

int checkFullNewLetters(char *str, Dico *occu) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (occu[str[i]-'a'].taille == -1) {
            return 0;
        }
    }
    return length;
}

int getIndexBiggerWordFullNewLetters(Dico dico, Dico* occu) {
    int length = dico.taille;
    int max = 0;
    int index = -1;
    for (int i = 0; i < length; i++) {
        int length_word_new_letters = checkFullNewLetters(dico.tab[i], occu);
        if (length_word_new_letters > max) {
            max = length_word_new_letters;
            index = i;
        }
    }

    return index;
}

//retourne le nombre de lettres encore non trouvées
int checkEnd(Dico *occu, int nombre_lettre) {
    int nb = 0;
    for (int i = 0; i < nombre_lettre; i++) {
        if (occu[i].taille != -1) {
            nb++;
        }
    }

    return nb;
}

int getSmallerWord(Dico *occu) {
    int i = 0;
    while (occu[i].taille < 0) {
        i++;
    }

    int taille_min = strlen(occu[i].tab[0]);
    int indexMin = 0;

    for (int j = 1; j < occu[i].taille; j++) {
        int taille = strlen(occu[i].tab[j]);
        if (taille < taille_min) {
            taille_min = taille;
            indexMin = j;
        }
    }

    return occu[i].tabInd[indexMin];
}

int getTaillePangramme(Dico d) {
    int length = d.taille;
    if (length == INT_MAX) {
        return length;
    }

    int nb = 0;
    for (int i = 0; i < length; i++) {
        nb += strlen(d.tab[i]);
    }

    return nb;
}

void printTaillePangramme(Dico res) {
    printf("%d", getTaillePangramme(res));
}

void printPangramme(Dico res) {
    int length = res.taille;
    for (int i = 0; i < length; i++) {
        printf(" %s", res.tab[i]);
    }
    printf("\n");
}

int my_strcmp(const void *a, const void *b) {
    const char *aa = *(const char**)a;
    const char *bb = *(const char**)b;
    return strcmp(aa, bb);
}

void printReponse(Dico *res) {
    printTaillePangramme(*res);
    qsort(res->tab, res->taille, sizeof(char*), my_strcmp);
    printPangramme(*res);
}

int motUtile(char *str, Dico *occu) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (occu[str[i]-'a'].taille != -1) {
            return 1;
        }
    }

    return 0;
}

void destroyDico(Dico d, int nombre_mot_dico) {
    free(d.tabInd);
    for (int i = 0; i < nombre_mot_dico; i++) {
        free(d.tab[i]);
    }
    free(d.tab);
}

void actualiseTabOccu(int tab_occu[], int nombre_lettre, Dico *occu) {
    for (int i = 0; i < nombre_lettre; i++) {
        tab_occu[i] = occu[i].taille;
    }
}

void afficherTab(char *str, int dico_taille, int taille_mot_max, char dico_tab[dico_taille][taille_mot_max+1]) {
    printf("%s: [", str);
    for (int i = 0; i < dico_taille; i++) {
        if (i != 0) { printf(", "); }
        printf("%s (%d)", dico_tab[i], (int)strlen(dico_tab[i]));
    }
    printf("]\n");
}

int actualiseTabDico(int dico_taille, int taille_mot_max, char dico_tab[dico_taille][taille_mot_max+1], Dico dico) {
    for (int i = 0; i < dico.taille; i++) {
        strcpy(dico_tab[i], dico.tab[i]);
    }
    return dico.taille;
}

int actualiseDico(int dico_taille, int taille_mot_max, char dico_tab[dico_taille][taille_mot_max+1], Dico dico) {
    for (int i = 0; i < dico.taille; i++) {
        strcpy(dico.tab[i], dico_tab[i]);
    }
    return dico_taille;
}

void actualiseOccu(int tab_occu[], int nombre_lettre, Dico *occu) {
    for (int i = 0; i < nombre_lettre; i++) {
         occu[i].taille = tab_occu[i];
    }
}

Dico rec(int tab_occu[], Dico dico, Dico res, Dico *occu, int nombre_lettre_non_trouve, int nombre_lettre, int taille_mot_max, int nombre_mot_dico, int indexWord, int dico_taille, int res_taille, char dico_tab[dico_taille][taille_mot_max+1], char res_tab[res_taille][taille_mot_max+1]) {
    //printf("\n**********************************\n"); //debug option
    //afficherDico("Dico", dico); //debug option
    //afficherOccu(occu, nombre_lettre); //debug option
    //afficherDico("Res", res); //debug option
    if (indexWord != -1) {
        //printf("ON PREND LUI: %s\n", dico.tab[indexWord]); //debug option
    } else {
        //printf("ON PREND RIEN\n"); //debug option
    }


    if (indexWord != -1) {
        push(dico.tab[indexWord], &res);
        checkLettreTrouve(dico.tab[indexWord], occu);
        popDico(indexWord, &dico, taille_mot_max, occu, nombre_lettre);
    }

    //printf("ON OBTIENT DONC:\n"); //debug option
    //afficherDico("Dico", dico); //debug option
    //afficherOccu(occu, nombre_lettre); //debug option
    //afficherDico("Res", res); //debug option
    getOccu(dico, nombre_lettre, occu);
    nombre_lettre_non_trouve = checkEnd(occu, nombre_lettre);

    // cas fini
    if (nombre_lettre_non_trouve == 0) {
        //printf("FIIIIIIINIIIIIIIIII\n"); //debug option
        return res;
    }

    //printf("MIN_TAB_OCCU=%d\n", minTab(occu, nombre_lettre)); //debug option
    // cas récursif si mot forcé
    if (minTab(occu, nombre_lettre) == 1) {
        int i = getMotForce(occu, nombre_lettre);
        return rec(tab_occu, dico, res, occu, checkEnd(occu, nombre_lettre), nombre_lettre, taille_mot_max, nombre_mot_dico, i, dico_taille, res_taille, dico_tab, res_tab);
    }

    if (nombre_lettre_non_trouve == 1) {
        int indexSmallerWord = getSmallerWord(occu);
        return rec(tab_occu, dico, res, occu, checkEnd(occu, nombre_lettre), nombre_lettre, taille_mot_max, nombre_mot_dico, indexSmallerWord, dico_taille, res_taille, dico_tab, res_tab);
    } else { // cas arbre (brute force)
        Dico res_tmp = initDico(taille_mot_max, nombre_mot_dico);
        Dico res_tmp_min = initDico(taille_mot_max, nombre_mot_dico);
        res_tmp_min.taille = INT_MAX;

        //afficherTab("DICO_TAB", dico_taille, taille_mot_max, dico_tab); //debug option
        //afficherTab("RES_TAB", res_taille, taille_mot_max, res_tab); //debug option

        // sauvegarde de occu dans tab_occu
        actualiseTabOccu(tab_occu, nombre_lettre, occu);
        // sauvegarde de dico dans dico_tab
        dico_taille = actualiseTabDico(dico_taille, taille_mot_max, dico_tab, dico);
        // sauvegarde de dico dans dico_tab
        res_taille = actualiseTabDico(res_taille, taille_mot_max, res_tab, res);

        for (int i = 0; i < dico.taille && motUtile(dico.tab[i], occu); i++) {
            //printf("\nCHOIX n°%d: %s\n", i, dico.tab[i]); //debug option
            res_tmp = rec(tab_occu, dico, res, occu, checkEnd(occu, nombre_lettre), nombre_lettre, taille_mot_max, nombre_mot_dico, i, dico_taille, res_taille, dico_tab, res_tab);

            int a = getTaillePangramme(res_tmp);
            int b = getTaillePangramme(res_tmp_min);
            //printf("BEST TAILLE PANGRAMME: %d | TAILLE PANGRAMME CURRENT RES: %d\n", b, a); //debug option
            if (res_tmp_min.taille == INT_MAX || a < b) {
                //printf("res_tmp.taille: %d < res_tmp_min.taille: %d\n", res_tmp.taille, res_tmp_min.taille); //debug option
                res_tmp_min = res_tmp;
            }

            actualiseOccu(tab_occu, nombre_lettre, occu);
            dico.taille = actualiseDico(dico_taille, taille_mot_max, dico_tab, dico);
            res.taille = actualiseDico(res_taille, taille_mot_max, res_tab, res);
            getOccu(dico, nombre_lettre, occu);
            nombre_lettre_non_trouve = checkEnd(occu, nombre_lettre);

            //printf("************ON REVIENT A CET ETAT************\n"); //debug option
            //afficherDico("Dico", dico); //debug option
            //afficherOccu(occu, nombre_lettre); //debug option
            //afficherDico("Res", res); //debug option
            //printf("*********************************************\n"); //debug option
        }

        return res_tmp_min;
    }
}

int main() {
    char derniere_lettre;
    int taille_mot_max = 0;
    int nombre_mot_dico = 0;
    scanf(" %c", &derniere_lettre);
    scanf(" %d", &taille_mot_max);
    scanf(" %d", &nombre_mot_dico);

    Dico dico = initDico(taille_mot_max, nombre_mot_dico);
    Dico res = initDico(taille_mot_max, nombre_mot_dico);
    int nombre_lettre = derniere_lettre - 'a' + 1;
    int nombre_lettre_non_trouve = nombre_lettre;
    Dico *occu = initOccu(taille_mot_max, nombre_mot_dico, nombre_lettre);

    int dico_taille = nombre_mot_dico;
    char dico_tab[dico_taille][taille_mot_max+1];
    int res_taille = nombre_mot_dico;
    char res_tab[res_taille][taille_mot_max+1];
    int tab_occu[nombre_lettre];
    actualiseTabOccu(tab_occu, nombre_lettre, occu);
    dico_taille = actualiseTabDico(dico_taille, taille_mot_max, dico_tab, dico);
    res_taille = actualiseTabDico(res_taille, taille_mot_max, res_tab, res);

    while (dico.taille != nombre_mot_dico) {
        scanf(" %s", dico.tab[dico.taille++]);
    }

    /* REPONSE A L'EXERCICE */
    getOccu(dico, nombre_lettre, occu);
    //afficherDico("Dico", dico); //debug option
    //afficherOccu(occu, nombre_lettre); //debug option

    // CAS ERREUR
    if (checkImpossible(occu, nombre_lettre)) {
        printf("0\n");
    } else {
        res = rec(tab_occu, dico, res, occu, nombre_lettre_non_trouve, nombre_lettre, taille_mot_max, nombre_mot_dico, -1, dico_taille, res_taille, dico_tab, res_tab);
        //printf("******SOLUTION******\n");
        printReponse(&res);
    }

    destroyDico(dico, nombre_mot_dico);
    for (int i = 0; i < nombre_lettre; i++) {
        destroyDico(occu[i], nombre_mot_dico);
    }
    free(occu);

    return 0;
}
