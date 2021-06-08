#include <stdio.h>
#include "pratica7.h"

int main() {
    int n, i = 0;
    int vec[3] = {1 ,2, 3}, vecInv[3];
    invertVec(vec, vecInv, 3);
    for (i = 0; i< 3; i++) {
        printf("%i ", vecInv[i]);
    }
}