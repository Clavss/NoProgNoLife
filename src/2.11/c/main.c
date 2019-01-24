#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

#define START 1;

typedef struct {
    int nbPave;
    int pathLength;
    int nbCarr;
    int *carrPos;
    int pos;
    int days;
} pavage;

int getNumber() {
    int nb;
    fscanf(stdin, "%d", &nb);
    return nb;
}

int *createTab(int nbCarr) {
    return (int *) malloc(nbCarr * sizeof(int));
}

void getPavage(pavage *p) {
    p->nbPave = getNumber();
    p->pathLength = getNumber();
    p->nbCarr = getNumber();
    p->carrPos = createTab(p->nbCarr);
    p->pos = START;
    p->days = 1;
    for (int i = 0; i < p->nbCarr; i++) {
        p->carrPos[i] = getNumber();
    }


}

void printPavage(pavage p) {
    printf("nbPave = %d\n", p.nbPave);
    printf("pathLength = %d\n", p.pathLength);
    printf("nbCarr = %d\n", p.nbCarr);
    printf("pos = %d\n", p.pos);
    printf("days = %d\n", p.days);
    for (int i = 0; i < p.nbCarr; i++) {
        printf("carrPos[%d] = %d\n", i, p.carrPos[i]);
    }
}

int finish(pavage p) {
    // printf("pos = %d, p.pathLength = %d",p.pos,p.pathLength);
    return p.pos >= p.pathLength;
}

int isCarr(int pos, pavage p) {
    for (int i = 0; i < p.nbCarr; i++) {
        if (p.carrPos[i] == pos) {
            return true;
        }
    }

    return false;
}

void avancer(pavage *p) {
    int pos = p->pos + p->nbPave;
    while (isCarr(pos, *p)) {
        pos--;
    }
    if (pos < 1) {
        p->pos = START;
    } else {
        p->pos = pos;
    }

}

void returnToCarr(pavage *p) {
    int reload = 0;
    p->days++;
    while (!isCarr(p->pos, *p)) {
        p->pos--;
        reload++;
    }

    p->nbPave += 10 * reload;
}

void startPavage(pavage *p) {
    avancer(p);
    while (!finish(*p)) {
        returnToCarr(p);
        avancer(p);
    }
    p->days++;
}

void start(pavage *p) {
    if ((p->nbCarr == 0) && (p->pathLength > p->nbPave)) {
        printf("%d", -1);
        return;
    }
    if(p->pathLength == 0) {
        printf("%d",0);
        return;
    }

    int canMove = false;

    for (int i = p->pos + p->nbPave; i > 1; i--) {
        if (!isCarr(i, *p)) {
            canMove = true;
        }
    }

    if(canMove) {
        startPavage(p);
        printf("%d", p->days);
    } else {
        printf("%d",-1);
    }


}

int main() {
    pavage p;
    getPavage(&p);
    start(&p);
    return 0;
}