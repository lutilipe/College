#include <stdio.h>
#include <string.h>

void main() {
    char name[20];

    scanf("%s", name);

    int lenght = strlen(name);

    for (int i = 0; i < lenght; i++) {
        printf("%d ", name[i]);
    }
}