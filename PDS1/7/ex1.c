#include <stdio.h>
#include "pratica7.h"

#define N 3

int main() {
    int vec1[N] = {2, 5, 6};
    int vec2[N] = {8, 9, 10};
    int result;

    result = escalar(vec1, vec2, N);
    printf("%i", result);
}