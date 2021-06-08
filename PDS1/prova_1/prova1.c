#include <stdio.h>

void imprimePilhas (int p1, int p2, int p3) {
    int p1_count,
        p2_count,
        p3_count;

    printf("\n%i ", p1);
    for (p1_count = 0; p1_count < p1; p1_count++) {
        printf("%c", '|');
    }
    printf("\n%i ", p2);
    for (p2_count = 0; p2_count < p2; p2_count++) {
        printf("%c", '|');
    }
    printf("\n%i ", p3);
    for (p3_count = 0; p3_count < p3; p3_count++) {
        printf("%c", '|');
    }
    printf("\n");
}

void imprimePilhas2 (int p1, int p2, int p3) {
    int max_number = 0,
        tmp_p1 = p1,
        tmp_p2 = p2,
        tmp_p3 = p3;

    if ((p1 > p2) && (p1 > p3)) {
        max_number = p1;
    } else if ((p2 > p1) && (p2 > p3)) {
        max_number = p2;
    } else {
        max_number = p3;
    }

    printf("\n");
    while (max_number > 0) {
        if (max_number == tmp_p1) {
            printf("%c ", '_');
            tmp_p1--;
        } else {
            printf("%c ", ' ');
        }

        if (max_number == tmp_p2) {
            printf("%c ", '_');
            tmp_p2--;
        } else {
            printf("%c ", ' ');
        }

        if (max_number == tmp_p3) {
            printf("%c", '_');
            tmp_p3--;
        } else {
            printf("%c ", ' ');
        }
        
        printf("\n");
        if (max_number == 1) {
            printf("%i %i %i", p1, p2, p3);
        }
        max_number--;
    }

    printf("\n");
}

void leJogada (int *end_p, int *end_q) {
    printf("Escolha uma pilha (1, 2 ou 3):\n");
    scanf("%i", end_p);
    printf("Quantos palitos gostaria de remover?\n");
    scanf("%i", end_q);
}

int diminuiPilha(int *end_p, int q) {
    if ((q <= 0) || (q > *end_p)) {
        return 0;
    } else {
        *end_p = *end_p - q;
        return 1;
    }
}

int confereJogo(int p1, int p2, int p3) {
    if ((p1 == 0) && (p2 == 0) && (p3 == 0)) {
        return 0;
    }

    return 1;
}

int jogo(int p1, int p2, int p3) {
    int jogador_atual = 1, 
        jogador_em_espera = 2,
        tmp,
        quantidade,
        pilha_escolhida,
        jogada_valida,
        jogo_finalizado;

    while (confereJogo(p1, p2, p3)) {
        do {
            imprimePilhas(p1, p2, p3);
            printf("Vez do jogador: %i\n", jogador_atual);
            leJogada(&pilha_escolhida, &quantidade);
            if (pilha_escolhida == 1) {
                jogada_valida = diminuiPilha(&p1, quantidade);
            } else if (pilha_escolhida == 2) {
                jogada_valida = diminuiPilha(&p2, quantidade);
            } else {
                jogada_valida = diminuiPilha(&p3, quantidade);
            }
            
            if (!jogada_valida) {
                printf("\nErro! Jogue novamente!\n");
            } else {
                tmp = jogador_atual;
                jogador_atual = jogador_em_espera;
                jogador_em_espera = tmp;
            }
        } while (!jogada_valida);
    }

    return jogador_atual;
}

int principal() {
    int p1, p2, p3;
    do {
        scanf("%i %i %i", &p1, &p2, &p3);
    } while ((p1 <= 0) || (p2 <= 0) || (p3 <= 0));
    return jogo(p1, p2, p3);
}

void main() {
    int resultado;
    resultado = principal();
    printf("O vencedor e: %i", resultado);
}