#include <stdio.h>
#include "pratica7.h"

#define N 20

int main() {
    int vec1[N] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    int vec2[N] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int vec3[N * 2];
    int i = 0;

    intercalate(vec1, vec2, vec3, N);
    for (i = 0; i < N; i++) {
        printf("%i\n", vec3[i]);
    }
}