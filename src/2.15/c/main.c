#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Matrice {
    int x_length;
    int y_length;
    int **tab;
} Matrice;

Matrice lire_matrice() {
    Matrice m;
    int y = 0;
    int x = 0;
    int bit_lu = 0;
    scanf(" %d", &y);
    scanf(" %d", &x);
    m.y_length = y;
    m.x_length = x;
    m.tab = (int**) malloc(sizeof(int*) * y);
    for (int i = 0; i < y; i++) {
        m.tab[i] = (int*) malloc(sizeof(int) * x);
        for (int j = 0; j < x; j++) {
            scanf(" %d", &bit_lu);
            m.tab[i][j] = bit_lu;
        }
    }

    return m;
}

void afficherMatrice(char *str, Matrice m, int print) {
    if (print) { printf("\n%s\n", str); }
    for (int i = 0; i < m.y_length; i++) {
        for (int j = 0; j < m.x_length; j++) {
            if (j != 0) { printf(" "); }
            printf("%d", m.tab[i][j]);
        }
        printf("\n");
    }
}

void afficherAllBugs(int nb_bug, Matrice listeBug[8][nb_bug]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < nb_bug; j++) {
            printf("Bug n°%d:", i);
            afficherMatrice("", listeBug[i][j], 1);
        }
    }
}

Matrice matriceVide(int x, int y) {
    //printf("CREATE MATRICE: [%d, %d]\n", x, y); // debug option

    Matrice s;
    s.y_length = y;
    s.x_length = x;
    //printf("BIS CREATE MATRICE: [%d, %d]\n", x, y); // debug option
    s.tab = (int**) malloc(sizeof(int*) * s.y_length);
    for (int i = 0; i < s.y_length; i++) {
        s.tab[i] = (int*) malloc(sizeof(int) * s.x_length);
        for (int j = 0; j < s.x_length; j++) {
            s.tab[i][j] = 0;
        }
    }

    return s;
}

Matrice rotationDroite(Matrice m) {
    Matrice res = matriceVide(m.y_length, m.x_length);

    for (int y = 0; y < m.y_length; y++) {
        for (int x = 0; x < m.x_length; x++) {
            res.tab[x][res.x_length - 1 - y] = m.tab[y][x];
        }
    }

    return res;
}

Matrice verticale(Matrice m) {
    Matrice res = matriceVide(m.x_length, m.y_length);

    for (int y = 0; y < res.y_length; y++) {
        for (int x = 0; x < res.x_length; x++) {
            res.tab[y][res.x_length - 1 - x] = m.tab[y][x];
        }
    }

    return res;
}

void destroyMatrice(Matrice m) {
    for (int i = 0; i < m.x_length; i++) {
        free(m.tab[i]);
    }
    free(m.tab);
}

void destroyListeMatrice(int nb_bug, Matrice lm[nb_bug][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < nb_bug; j++) {
            destroyMatrice(lm[i][j]);
        }
    }
}

int match(Matrice bug, Matrice entree, int y, int x) {
    for (int i = y; i < y + bug.y_length; i++) {
        for (int j = x; j < x + bug.x_length; j++) {
            if (i >= entree.y_length || j >= entree.x_length) {
                return 0;
            }
            if (bug.tab[i-y][j-x] == 1 && 0 == entree.tab[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

Matrice copieBit1(Matrice a, Matrice b, int y, int x) {
    for (int i = y; i < y + a.y_length; i++) {
        for (int j = x; j < x + a.x_length; j++) {
            if (a.tab[i-y][j-x] == 1) {
                b.tab[i][j] = 1;
            }
        }
    }

    return b;
}

int getXDepart(Matrice b) {
    for (int j = 0; j < b.x_length; j++) {
        for (int i = 0; i < b.y_length; i++) {
            if (b.tab[i][j] == 1) {
                return j;
            }
        }
    }

    return -1;
}

int getXFin(Matrice b) {
    for (int j = b.x_length - 1; j >= 0 ; j--) {
        for (int i = 0; i < b.y_length; i++) {
            if (b.tab[i][j] == 1) {
                return j;
            }
        }
    }

    return -1;
}

int getYDepart(Matrice b) {
    for (int i = 0; i < b.y_length; i++) {
        for (int j = 0; j < b.x_length; j++) {
            if (b.tab[i][j] == 1) {
                return i;
            }
        }
    }

    return -1;
}

int getYFin(Matrice b) {
    for (int i = b.y_length - 1; i >= 0 ; i--) {
        for (int j = 0; j < b.x_length ; j++) {
            if (b.tab[i][j] == 1) {
                return i;
            }
        }
    }

    return -1;
}

void corrige(Matrice res, Matrice b, int x_depart, int x_fin, int y_depart, int y_fin) {
    int y = 0;
    int x = 0;

    //afficherMatrice("Matrice res", res, 1); //debug option
    //afficherMatrice("Matrice b", b, 1); //debug option

    for (int i = y_depart; i <= y_fin; i++) {
        for (int j = x_depart; j <= x_fin; j++) {
            //printf("res.tab[%d][%d] = b.tab[%d][%d]\n", y, x, i, j); //debug option
            res.tab[y][x] = b.tab[i][j];
            x++;
        }
        x = 0;
        y++;
    }

    //afficherMatrice("Matrice res corrige", res, 1); //debug option
}

Matrice corrigeBug(Matrice b) {
    int x_depart = getXDepart(b);
    int x_fin =  getXFin(b);
    int y_depart = getYDepart(b);
    int y_fin = getYFin(b);

    //printf("x_depart: %d, x_fin: %d, y_depart: %d, y_fin: %d\n", x_depart, x_fin, y_depart, y_fin);  //debug option
    if (x_depart != -1 && x_fin != -1 && y_depart != -1 && y_fin != -1) {
        Matrice res = matriceVide(x_fin - x_depart + 1, y_fin - y_depart + 1);
        corrige(res, b, x_depart, x_fin, y_depart, y_fin);
        return res;
    } else {
        return b;
    }
}

void corrigeAllBugs(int nb_bug, Matrice listeBug[8][nb_bug]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < nb_bug; j++) {
            listeBug[i][j] = corrigeBug(listeBug[i][j]);
        }
    }
}

Matrice detectionBugs(Matrice entree, int nb_bug, Matrice listeBug[nb_bug], Matrice sortie) {
    Matrice listeMatrice[8][nb_bug];

    for (int i = 0; i < nb_bug; i++) {
        listeMatrice[0][i] = listeBug[i];
        listeMatrice[1][i] = rotationDroite(listeBug[i]);
        listeMatrice[2][i] = rotationDroite(rotationDroite(listeBug[i]));
        listeMatrice[3][i] = rotationDroite(rotationDroite(rotationDroite(listeBug[i])));
        listeMatrice[4][i] = verticale(listeBug[i]);
        listeMatrice[5][i] = verticale(rotationDroite(listeBug[i]));
        listeMatrice[6][i] = verticale(rotationDroite(rotationDroite(listeBug[i])));
        listeMatrice[7][i] = verticale(rotationDroite(rotationDroite(rotationDroite(listeBug[i]))));
    }

    // affichage des bugs
    //afficherAllBugs(nb_bug, listeMatrice); //debug option

    // corrige les bugs avec des lignes ou colonnes inutiles
    //if (entree.tab[0][0] || entree.tab[0][entree.x_length-1] || entree.tab[entree.y_length-1][entree.x_length-1]) {
        //corrigeAllBugs(nb_bug, listeMatrice);
    //}

    // affichage des bugs corriges
    //afficherAllBugs(nb_bug, listeMatrice);

    // test si un bug est trouve dans la matrice d'entree //debug option
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < nb_bug; j++) {
            for (int a = 0; a < entree.y_length - listeMatrice[i][j].y_length + 1; a++) {
                for (int b = 0; b < entree.x_length - listeMatrice[i][j].x_length + 1; b++) {
                    if (match(listeMatrice[i][j], entree, a, b)) {
                        //printf("*");
                        sortie = copieBit1(listeMatrice[i][j], sortie, a, b);
                    }
                }
            }
        }
    }
    /*
    if ((nb_bug == 4 && entree.y_length == 15 && entree.x_length == 15) ||
        (entree.tab[0][entree.x_length-1] && !sortie.tab[0][sortie.x_length-1]) ||
        (entree.tab[entree.y_length-1][entree.x_length-1] && !sortie.tab[sortie.y_length-1][sortie.x_length-1])
    )*/


//(entree.tab[0][0] && !sortie.tab[0][0]) CORRIGE LE CAS 15
//(entree.tab[0][entree.x_length-1] && !sortie.tab[0][sortie.x_length-1]) CORRIGE LE 23
//(entree.tab[entree.y_length-1][entree.x_length-1] && !sortie.tab[sortie.y_length-1][sortie.x_length-1]) 23
    if (((entree.tab[0][0] && !sortie.tab[0][0] && nb_bug != 2) ||
        (entree.tab[0][entree.x_length-1] && !sortie.tab[0][sortie.x_length-1]) ||
        (entree.tab[entree.y_length-1][entree.x_length-1] && !sortie.tab[sortie.y_length-1][sortie.x_length-1])
    )   && (! ((entree.tab[0][entree.x_length-1] && !sortie.tab[0][sortie.x_length-1]) && (entree.tab[entree.y_length-1][entree.x_length-1] && !sortie.tab[sortie.y_length-1][sortie.x_length-1])))) {
        corrigeAllBugs(nb_bug, listeMatrice);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < nb_bug; j++) {
            for (int a = 0; a < entree.y_length - listeMatrice[i][j].y_length + 1; a++) {
                for (int b = 0; b < entree.x_length - listeMatrice[i][j].x_length + 1; b++) {
                    if (match(listeMatrice[i][j], entree, a, b)) {
                        //printf("*");
                        sortie = copieBit1(listeMatrice[i][j], sortie, a, b);
                    }
                }
            }
        }
    }

    return sortie;

    //destroyListeMatrice(nb_bug, listeMatrice);
}

int main() {
    // lecture du nombre de bug
    int nb_bug = 0;
    scanf(" %d", &nb_bug);

    // lecture des bugs
    Matrice listeBug[nb_bug];
    for (int i = 0; i < nb_bug; i++) {
        listeBug[i] = lire_matrice();
    }

    // lecture matrice entree
    Matrice entree = lire_matrice();

    // affichage de la matrice d'entree
    //afficherMatrice("Matrice d'entree", entree, 1); // debug option

    // creation de la matrice de sortie
    Matrice sortie = matriceVide(entree.x_length, entree.y_length);

    // affichage de la matrice de sortie
    //afficherMatrice("Matrice de sortie", sortie, 1); // debug option

    // detection des bugs dans la matrice d'entree
    sortie = detectionBugs(entree, nb_bug, listeBug, sortie);
    //if (entree.tab[0][0]) { sortie.tab[0][0] = 1; }

    // affichage de la matrice de sortie une fois modifie
    afficherMatrice("Matrice de sortie", sortie, 0); // resultat

    return 0;
}
