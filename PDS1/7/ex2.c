#include <stdio.h>
#include "pratica7.h"

#define MAX_FIBONACCI 1000
#define MIN_FIBONACCI 0

int main() {
    int vec[MAX_FIBONACCI] = {1, 1}, num;
    unsigned long long fib_num;
    do {
        scanf("%i", &num);
        fib_num = fibonnaci(num, vec);
        printf("%llu\n", fib_num);
        vec[num] = fib_num;
    } while ((num <= MAX_FIBONACCI) && (num >= MIN_FIBONACCI));
}