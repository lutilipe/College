#include <stdio.h>

void main() {
    int count, dezena, unidade, produto, lastNumber;
    int total = 0;
    for (count = 2; count < 11; count++) {
        int curr;
        scanf("%i", &curr);
        if (count == 2) {
            lastNumber = curr * (count);
        }
        total = total + curr * (count);
    }

    printf("%i", lastNumber);

    if (total % 11 <= 1) {
        dezena = 0;
    } else {
        dezena = 11 - (total % 11);
    }

    produto = total - lastNumber + dezena * 10;

    if (produto % 11 <= 1) {
        unidade = 0;
    } else {
        unidade = 11 - (produto % 11);
    }

    printf("%i%i", dezena, unidade);
}