#include <stdio.h>
#include "pratica6.h"

int main() {
    int length = 0, count = 0, tmpLength;
    char currChar;
    char str[128];
    char inverse[128];
    do {
        currChar = getc(stdin);
        str[length] = currChar;
        length++;
    } while (currChar != '.');
    tmpLength = length;
    inverse[length] = '\0';
    length -= 2;
    while (length >= 0) {
        inverse[count] = str[length];
        length--;
        count++;
    }
    printf("%s", inverse);
}