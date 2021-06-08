#include <stdio.h>
#include "pratica6.h"

int main() {
    int isPalindrome;
    char str[] = "reviver";
    isPalindrome = palindrome(str);
    printf("\n%i", isPalindrome);
    return 1;
}