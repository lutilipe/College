#include "pratica6.h"
#include <stdio.h>

unsigned int factorial(int i) {
    unsigned int result = 1;
    while (i > 0) {
        result *= i;
        i--;
    }

    return result;
}

char conceito(int i) {
    char grade;
    switch (i)
    {
    case 0:
        grade = 'F';
        break;
    case 1:
        grade = 'F';
        break;
    case 2:
        grade = 'F';
        break;
    case 3:
        grade = 'F';
        break;
    case 4:
        grade = 'F';
        break;
    case 5:
        grade = 'E';
        break;
    case 6:
        grade = 'D';
        break;
    case 7:
        grade = 'C';
        break;
    case 8:
        grade = 'B';
        break;
    case 9:
        grade = 'A';
        break;
    default:
        grade = 'A';
        break;
    }

    return grade;
}

void floyd(int line) {
    int i, j, count = 0;

    for (i = 0; i < line; i++) {
        for (j = 0; j < i; j++) {
            count++;
            printf("%i ", count);
        }
        printf("\n");
    }
}

int stringLength(char str[]) {
    int result = 0, count = 0;
    while (str[count] != '\0') {
        result++;
        count++;
    }

    return result;
}

void modifyASCII(char str[]) {
    int length = stringLength(str), count, currChar;
    for (count = 0; count < length; count++) {
        currChar = (int) str[count];
        if ((currChar <= 122) && (currChar >= 97)) {
            str[count] = (char) (currChar - 32);
        }
    }
}

int palindrome(char str[]) {
    int length = stringLength(str) - 1, 
        i, 
        result = 0;
    for (i = 0; i < length; i++) {
        if (str[i] == str[length]) {
            length--;
            result++;
        }
    }
    return result == length;
}