#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TAM 100

typedef struct Bloco {
	int linha, coluna, tam;
} Bloco;

typedef struct Ponto {
    float x, y;
} Ponto;

typedef struct Circulo {
    Ponto centro;
    float raio;
} Circulo;

typedef struct Retangulo {
    Ponto sup_esq, inf_dir; 
} Retangulo;

//1)

void printMatriz(int M[][MAX_TAM], int n) {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%5d", M[i][j]);
        }
    printf("\n");
    }
}

void zeraMatriz(int M[][MAX_TAM], int n) {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            M[i][j] = 0;
        }
    }
}


//2)

int insereBloco(int M[][MAX_TAM], int n, Bloco b) {
    if (b.linha + b.tam > n) return 0;
    if (b.coluna + b.tam > n) return 0;
    
    int i = 0, j = 0;

    for (i = b.linha; i < b.tam + b.linha; i++) {
        for (j = b.coluna; j < b.tam + b.coluna; j++) {
            M[i][j] = 1;
        }
    }
    return 1; 
}

//3)

Bloco maiorBloco(int M[][MAX_TAM], int n, int i, int j) {
    Bloco b;
    int w = 0, 
        z = 0, 
        maxI = 0, 
        maxJ = 0, 
        maxSize = 0, 
        size = 0, 
        totalSize = 0,
        count = 0;

    b.linha = i;
    b.coluna = j;

    if (M[i][j] != 1) {
        b.tam = 0;
        return b;
    }

    for(w = i; w < n; w++) { 
        if (M[w][j]) maxJ += 1;              
    } 

    for(w = j; w < n; w++) { 
        if (M[i][w]) maxI += 1;              
    } 

    if (maxI > maxJ) maxSize = maxJ;
    else if (maxJ >= maxI) maxSize = maxI;

    if (maxSize == 1) {
        b.tam = maxSize;
        return b;
    }

    if (maxI == maxSize) {
        while (maxSize > 0) {
            count = 0;
            for(w = i; w < n; w++) { 
                size = 0;
                for(z = j; z < n; z++) {
                    if (M[w][z] == 1) {
                        size++;
                    };              
                }  
                if (size == maxSize) {
                    count++;
                }  

                if (count == maxSize) {
                    b.tam = count;
                    return b;
                }          
            } 
            maxSize--;
        }
    } else {
        while (maxSize > 0) {
            count = 0;
            for(z = j; z < n; z++) { 
                size = 0;
                for(w = i; w < n; w++) {
                    if (M[w][z] == 1) {
                        size++;
                    };              
                }  
                if (size == maxSize) {
                    count++;
                }  

                if (count == maxSize) {
                    b.tam = count;
                    return b;
                }          
            } 
            maxSize--;
        }
    }
}

//4)

int marcarBloco(int M[][MAX_TAM], Bloco bloco) {
    int i = 0, j = 0;

    if (bloco.tam == 0) return 0;

    for (i = bloco.linha; i < bloco.linha + bloco.tam; i++) {
        for (j = bloco.coluna; j < bloco.coluna + bloco.tam; j++) {
           if (M[i][j] == 2) {
               return 0;
           }
           M[i][j] = 2;
        }
    }

    return 1;
}

void encontraBlocos(int M[][MAX_TAM], int n, Bloco blocos[], int *numBlocos) {
    int i, j, count = 0, blockMarked;
    Bloco b;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            b = maiorBloco(M, n, i, j);
            if (marcarBloco(M, b)) {
                blocos[count] = b;
                count++;
                *numBlocos += 1;
            }
        }
    }

    for (i = 0; i < count; i++) {
        printf("i:%i j:%i tam:%i %i\n", blocos[i].linha, blocos[i].coluna, blocos[i].tam, *numBlocos);
    }
}

//5) 

int stringLength(char str[]) {
    int result = 0, count = 0;
    while (str[count] != '\0') {
        result++;
        count++;
    }

    return result;
}

void toLowerCase(char str[], int length) {
    int i = 0, charNum;
    for (i = 0; i < length; i++) {
        charNum = (int) str[i];
        if (charNum >= 65 && charNum <= 90) {
            charNum += 32;
            str[i] = (char) charNum;
        }
    }
}

int numCharsDiferentes(char str[]) {
    int length = stringLength(str);
    int result = 0, i = 0, j = 0, appers;

    toLowerCase(str, length);

    for (i = 0; i < length; i++) {
        int appears = 0;
        for (j = 0; j < i; j++){
            if (str[j] == str[i]){
                appears = 1;
                break;
            }
        }

        if (!appears){
            result++;
        }
    }

    return result;
}

// 6

float calculoAlturaRetangulo(Retangulo ret) {
    return fabs(ret.inf_dir.y - ret.sup_esq.y);
}

float calculoLarguraRetangulo(Retangulo ret) {
    return fabs(ret.sup_esq.x - ret.inf_dir.x);
}

Ponto acharCentroRetangulo(Retangulo ret) {
    Ponto centro;
    centro.x = (ret.sup_esq.x + ret.inf_dir.x) / 2;
    centro.y = (ret.sup_esq.y + ret.inf_dir.y) / 2;
    return centro;
}

int colisaoCirculoRetangulo(Circulo cir, Retangulo ret) {
    float retH = calculoAlturaRetangulo(ret);
    float retW = calculoLarguraRetangulo(ret);
    Ponto retCentro = acharCentroRetangulo(ret);

    float distX = fabs(cir.centro.x - retCentro.x);
    float distY = fabs(cir.centro.y - retCentro.y);

    if (distX > (retW / 2 + cir.raio)) return 0; 
    if (distY > (retH / 2 + cir.raio)) return 0;

    if (distX <= (retW / 2)) return 1;
    if (distY <= (retH / 2)) return 1;

    float dx = distX - retW / 2;
    float dy = distY - retH / 2;
    
    return (dx*dx+dy*dy <= (cir.raio*cir.raio));
}

// 0

void main() {
    /* int matriz[MAX_TAM][MAX_TAM] , i = 0;
    zeraMatriz(matriz, 5);
    Bloco bloco;
    Bloco bloco3;
    Bloco bloco2[MAX_TAM];
    bloco.linha = 1;    
    bloco.coluna = 2;    
    bloco.tam = 3;    
    insereBloco(matriz, 5, bloco);
    bloco.linha = 4;    
    bloco.coluna = 0;    
    bloco.tam = 1;   
    insereBloco(matriz, 5, bloco); 
    bloco.linha = 4;    
    bloco.coluna = 0;    
    bloco.tam = 1;   
    insereBloco(matriz, 5, bloco);
    printMatriz(matriz, 5);
    printf("\n");
    encontraBlocos(matriz, 5, bloco2, &i); */
    /* char str[MAX_TAM] = "Adoro programar em C!";
    int result = numCharsDiferentes(str);
    printf("%i\n", result);
    for (int i = 0; i < stringLength(str); i++) {
        printf("%c", str[i]);
    } */
    Circulo cir;
    Retangulo ret;
    int result;

    cir.centro.x = 0;
    cir.centro.y = 0;
    cir.raio = 10;

    ret.sup_esq.x = -5;
    ret.sup_esq.y = 10;
    ret.inf_dir.x = 5;
    ret.inf_dir.y = -20;

    result = colisaoCirculoRetangulo(cir, ret);
    printf("%i\n", result);
}