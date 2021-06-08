#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM 1000

//1)

int contaLinhasArquivo(char nome_arquivo[]) {
    int nLines = 0;
    FILE *arq = fopen(nome_arquivo, "r");

    if (arq == NULL) return 0;

    while (!feof(arq)) {
        char c = getc(arq);
        if (c == '\n' || c == -1) nLines += 1;
    }
    fclose(arq);
    return nLines;
}


//2)

char** carregaPoema(char nome_arquivo[]) {
    int nLines = contaLinhasArquivo(nome_arquivo), i = 0, j = 0, lChar = 0;
    char **poem = NULL, c , tmp_str[MAX_TAM];
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL) return NULL;

    poem = (char**)malloc(nLines * sizeof(char*));
    while (!feof(arq)) {
        if (i == nLines - 1) break;
        
        c = getc(arq);
        tmp_str[lChar] = c;
        lChar++;

        if (c == '\n') {
            poem[i] = (char*)malloc(lChar * sizeof(char));
            for (j = 0; j < lChar; j++) {
                poem[i][j] = tmp_str[j];
                printf("%c", poem[i][j]);
            }
            i++;
            lChar = 0;
        }
    }
    poem[nLines - 1] = NULL;
    fclose(arq);
    return poem;
}

//3) 

void imprimeLinhaInvertida(char *line) {
    if (*line == '\n') {
        printf("\n");
        return;
    };
    imprimeLinhaInvertida(line + 1);
    printf("%c", *line);
}

void imprimePoemaInvertido(char **poema) {
    if (*poema == NULL) {
        return;
    };
    imprimePoemaInvertido(poema+1);
    imprimeLinhaInvertida(*poema);
}

//4)

int numeroTriangular(int n) {
    if (n == 0) return 0;
    return n + numeroTriangular(n-1);
}

//5)

float serieDois(int n) {
    if (n == 0) return 0.0;
    int denominador = numeroTriangular(n);
    return (1.0 / denominador) + serieDois(n-1);
}

// main auxiliar para testes:
int main() {
    printf("%i\n", contaLinhasArquivo("poema.txt"));
	return 0;
}
