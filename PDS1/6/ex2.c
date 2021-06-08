#include <stdio.h>
#include "pratica6.h"

int main() {
    int grade;
    do {
        scanf("%i", &grade);
    } while (grade < 0);

    printf("%c", conceito(grade));
    return 1;
}