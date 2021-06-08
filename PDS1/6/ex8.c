#include <stdio.h>
#include "pratica6.h"

int main() {
    char str[128], nome[128], c;
    int i = 0, j=0, l = 0;
    do {
        c = getc(stdin);
        str[i] = c;
        i++;
    } while (c != '.');
    str[i - 2] == '\0';
    l = i - 2;
    i = 0;
    while (i < l) {
        if ((((int) str[i] >= 97) && ((int) str[i] <= 122)) || str[i] == ' ') {
            i++;
            continue;
        }

        nome[j] = str[i];
        nome[j+1] = '.';
        j+=2;
        i++;
    }

    printf("\n%s", nome);
}