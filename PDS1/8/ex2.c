#include <stdio.h>
#include "redesocial.h"

void main() {
    popularRedeSocialAleatoriamente(0.6);
    imprimirRedeSocial();
    int n = numAmigosEmComum(1,6);
    printf("\nnumero de amigos em comum entre 2 e 4: %d\n", n); //gabarito: 2
    printf("coef. de aglomeracao da pessoa 2 eh: %.2f\n", coeficienteAglomeracao(3));
    //gabarito: 0.67 ***** (não é garantido, depende da ordem dos rands().
}
