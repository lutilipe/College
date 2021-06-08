#include <stdio.h>
#include "getche.h"
#include <stdlib.h>

#define BUFFER_TAM 5

int main() {
    char c , *string = NULL, *auxstring = NULL;
    int countBuffer = 0, countTotal = 0, i =0;
    char buffer[BUFFER_TAM];

    do {
        c = getche();
        if(c == '\r'){
            c = '\n';
            printf("\n");
        }

        if (countBuffer < BUFFER_TAM) {
            buffer[countBuffer] = c;
            countBuffer++;
        }

        if (countBuffer == BUFFER_TAM || c == '#') {
            auxstring = (char*) malloc((countTotal + countBuffer)*sizeof(char));
            for (i = 0; i < countTotal; i++) {
                auxstring[i] = string[i];
            }
            for (i = 0; i < countBuffer; i++) {
                auxstring[countTotal+i] = buffer[i];
            }
            if (string != NULL) {
                free(string);
            }
            string = auxstring;
            countTotal += countBuffer;
            countBuffer = 0;
        } 
    } while(c != '#');
    string[countTotal-1] = '\0';
    printf("\n%s\n", string);
    free(string);
    return 0;
}