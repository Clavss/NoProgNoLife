#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_MAX 20

void afficher(int inputs[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i != 0) { printf(", "); }
        printf("%d", inputs[i]);
    }
    printf("]\n");
}

int calculatrice(int taille, char str[]) {
    return 0;
}

char *grammaire(char *src) {
    return NULL;
}

int mult(int a, int b) {
    return a*b;
}

int add(int a, int b) {
    return a+b;
}

int sub(int a, int b) {
    return a-b;
}

int division(int a, int b) {
    return (a%b)
            ? (0)
            : (a/b);
}

int my_pow(int a, int b) {
    if (!b) { return 1; }
    int res = 1;
    for (int i = 0; i < b; i++) {
        res *= a;
    }
    return res;
}

int main() {
    int cnt_input = 0;
    int inputs[N_MAX];
    int number_read;

    scanf(" %d", &number_read);
    while (!feof(stdin) && cnt_input <= N_MAX) {
        inputs[cnt_input++] = number_read;
        scanf(" %d", &number_read);
    }

    /* REPONSE A L'EXERCICE */
    //afficher(inputs, cnt_input);
    afficher(inputs, cnt_input);
    for (int i = 0; i < 20; i++) {
        printf("n = %d : %d\n", i, my_pow(4, i-1)*my_pow(2, i));
    }

    return 0;
}
