#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH_NUMBER_MAX 10000

int containsOnlyDigit(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
     return 1;
}

int main() {
    int total = 0;
    int cnt_number = 0;
    char number_string[LENGTH_NUMBER_MAX];
    
    scanf(" %s", number_string);
    while (!feof(stdin)) {
        total += atoi(number_string);
        cnt_number += containsOnlyDigit(number_string);
        scanf(" %s", number_string);
    }
    
    printf("%d\n", total / cnt_number);
     
    return 0;
}