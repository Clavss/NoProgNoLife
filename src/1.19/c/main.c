#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PANNEAU_MAX 1000000
#define NORD 1
#define EST 2
#define SUD 3
#define OUEST 4

typedef struct Resultat {
    int taille;
    char tab[PANNEAU_MAX];
} Resultat;

typedef struct Perso {
    int x;
    int y;
    char current_dir;
} Perso;

void initPerso(Perso* perso, int x, int y) {
    perso->x = x;
    perso->y = y;
    perso->current_dir = 'N';
}

void afficher(int Y, int  X, char tab[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%c", tab[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void afficherPerso(Perso perso) {
    printf("PERSO: [%d, %d], %c\n", perso.x, perso.y, perso.current_dir);
}

void printPanneau(int panneau, Resultat* res) {
    switch (panneau) {
        case NORD:
            res->tab[res->taille++] = 'N';
        break;
        case EST:
            res->tab[res->taille++] = 'E';
        break;
        case SUD:
            res->tab[res->taille++] = 'S';
        break;
        case OUEST:
            res->tab[res->taille++] = 'O';
        break;
        default:
            res->tab[res->taille++] = '?';
        break;
    }
}

int isAtBord(Perso perso, int Y, int X, int dir_boussole) {
    return (perso.x == 0 && ((perso.current_dir == 'O' && dir_boussole == NORD)
                            || (perso.current_dir == 'S' && dir_boussole == EST)
                            || (perso.current_dir == 'E' && dir_boussole == SUD)
                            || (perso.current_dir == 'N' && dir_boussole == OUEST)))
        || (perso.x == X-1 && ((perso.current_dir == 'E' && dir_boussole == NORD)
                                || (perso.current_dir == 'N' && dir_boussole == EST)
                                || (perso.current_dir == 'O' && dir_boussole == SUD)
                                || (perso.current_dir == 'S' && dir_boussole == OUEST)))
        || (perso.y == 0 && ((perso.current_dir == 'N' && dir_boussole == NORD)
                                || (perso.current_dir == 'O' && dir_boussole == EST)
                                || (perso.current_dir == 'S' && dir_boussole == SUD)
                                || (perso.current_dir == 'E' && dir_boussole == OUEST)))
        || (perso.y == Y-1 && ((perso.current_dir == 'S' && dir_boussole == NORD)
                                || (perso.current_dir == 'E' && dir_boussole == EST)
                                || (perso.current_dir == 'N' && dir_boussole == SUD)
                                || (perso.current_dir == 'O' && dir_boussole == OUEST)));
}

int getNextPanneau(int Y, int X, char salle[Y][X], Perso* perso, int dir_boussole) {

    while (salle[perso->y][perso->x] == '.' || salle[perso->y][perso->x] == 'X') {
        if (isAtBord(*perso, Y, X, dir_boussole)) {
            return -1;
        }

        switch (dir_boussole)  {
            case NORD:
                switch (perso->current_dir) {
                    case 'N':
                        if (perso->y) {
                            perso->y--;
                        }
                    break;
                    case 'E':
                        if (perso->x != X-1) {
                            perso->x++;
                        }
                    break;
                    case 'S':
                        if (perso->y != Y-1) {
                            perso->y++;
                        }
                    break;
                    case 'O':
                        if (perso->x) {
                            perso->x--;
                        }
                    break;
                }
            break;
            case OUEST:
                switch (perso->current_dir) {
                    case 'E':
                        if (perso->y) {
                            perso->y--;
                        }
                    break;
                    case 'S':
                        if (perso->x != X-1) {
                            perso->x++;
                        }
                    break;
                    case 'O':
                        if (perso->y != Y-1) {
                            perso->y++;
                        }
                    break;
                    case 'N':
                        if (perso->x) {
                            perso->x--;
                        }
                    break;
                }
            break;
            case SUD:
                switch (perso->current_dir) {
                    case 'S':
                        if (perso->y) {
                            perso->y--;
                        }
                    break;
                    case 'O':
                        if (perso->x != X-1) {
                            perso->x++;
                        }
                    break;
                    case 'N':
                        if (perso->y != Y-1) {
                            perso->y++;
                        }
                    break;
                    case 'E':
                        if (perso->x) {
                            perso->x--;
                        }
                    break;
                }
            break;
            case EST:
                switch (perso->current_dir) {
                    case 'O':
                        if (perso->y) {
                            perso->y--;
                        }
                    break;
                    case 'N':
                        if (perso->x != X-1) {
                            perso->x++;
                        }
                    break;
                    case 'E':
                        if (perso->y != Y-1) {
                            perso->y++;
                        }
                    break;
                    case 'S':
                        if (perso->x) {
                            perso->x--;
                        }
                    break;
                }
            break;
        }
    }

    switch(salle[perso->y][perso->x]) {
        case 'N':
            return NORD;
        case 'E':
            return EST;
        case 'S':
            return SUD;
        case 'O':
            return OUEST;
        default:
            printf("salle[%d, %d] = %c\n", perso->y, perso->x, salle[perso->y][perso->x]);
            return 0;
    }
}

void sortie(int Y, int X, char salle[Y][X], Perso* perso, int dir_boussole, Resultat* res) {
    int panneau = 0;
    panneau = getNextPanneau(Y, X, salle, perso, dir_boussole);

    while (panneau != -1) {
        switch (panneau) {
            case NORD:
                perso->current_dir = 'N';
            break;
            case EST:
                perso->current_dir = 'E';
            break;
            case SUD:
                perso->current_dir = 'S';
            break;
            case OUEST:
                perso->current_dir = 'O';
            break;
            default:
                exit -2;
        }
        salle[perso->y][perso->x] = '.';
        printPanneau(panneau, res);

        panneau = getNextPanneau(Y, X, salle, perso, dir_boussole);
    }
}

void printSortie(Resultat res) {
    for (int i = 0; i < res.taille; i++) {
        printf("%c", res.tab[i]);
    }
    printf("\n");
}

int main() {
    char c_read;
    int X;
    int Y;
    int current_y = 0;
    int current_x = 0;
    int dir_boussole = 0;
    Perso celestine;
    Resultat res;
    res.taille = 0;

    scanf("%d %d\n", &X, &Y);

    char salle[Y][X];

    scanf("%c", &c_read);
    while (!feof(stdin)) {
        if (isdigit(c_read)) {
            dir_boussole = c_read - '0';
        } else if (c_read == 'X') {
            initPerso(&celestine, current_x, current_y);
            salle[current_y][current_x++] = c_read;
        } else if (c_read == '\n') {
            current_x = 0;
            current_y++;
        } else {
            salle[current_y][current_x++] = c_read;
        }

        scanf("%c", &c_read);
    }

    //afficher(Y, X, salle); //debug option
    //afficherPerso(celestine); //debug option

    /* REPONSE A L'EXERCICE */
    sortie(Y, X, salle, &celestine, dir_boussole, &res);
    printSortie(res);

    return 0;
}
