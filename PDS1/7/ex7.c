#include <stdio.h>
#include "pratica7.h"

#define N 5000000
#define LENGTH 1000

int main() {
    int result;
    result = randRep(N, LENGTH);
    printf("%i", result);
}