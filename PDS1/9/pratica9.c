#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Guerreiro {
    int ataque;
    int defesa; 
    int carisma;
    int pontos_vida;
    int id_guerreiro;
} Guerreiro;

int randomInt(int n) {
    return rand() % n;
}

int rolaDados() { 
    return (1 + randomInt(6)) + (1 + randomInt(6)) + (1 + randomInt(6));
}

void criaGuerreiro(Guerreiro *guerreiro) {
    guerreiro->ataque = rolaDados();
    guerreiro->defesa = rolaDados();
    guerreiro->carisma = rolaDados();
    guerreiro->pontos_vida = rolaDados() + rolaDados() + rolaDados();
}

int bonusCarisma(int carisma) {
    if (carisma == 18) {
        return 3;
    } else if (carisma == 16 || carisma == 17) {
        return 2;
    } else if (carisma == 14 || carisma == 15) {
        return 1;
    } else if (carisma == 6 || carisma == 7) {
        return -1;
    } else if (carisma == 4 || carisma == 5) {
        return -2;
    } else if (carisma == 3) {
        return -3;
    } else {
        return 0;
    }
}

void ataque(Guerreiro *guerreiro1, Guerreiro *guerreiro2) {
    int golpe = rolaDados() + guerreiro1->ataque + bonusCarisma(guerreiro1->carisma);
    int escudo = rolaDados() + guerreiro1->defesa + bonusCarisma(guerreiro1->carisma);
    int dano = golpe - escudo;
    printf("Ataque: %i - Defesa: %i\n", guerreiro1->id_guerreiro, guerreiro2->id_guerreiro);
    printf("PV1: %i - PV2: %i\n", guerreiro1->pontos_vida, guerreiro2->pontos_vida);
    printf("Golpe: %i - Escudo: %i - Dano: %i\n", golpe, escudo, dano);
    if (dano > 0) {
        guerreiro2->pontos_vida -= dano;
        if (guerreiro2->pontos_vida < 0) {
            guerreiro2->pontos_vida = 0;
        }
    }
}

void jogo() {
    int atacante = 1;

    Guerreiro guerreiro1, guerreiro2;
    guerreiro1.id_guerreiro = 1;
    guerreiro2.id_guerreiro = 2;

    criaGuerreiro(&guerreiro1);
    criaGuerreiro(&guerreiro2);

    printf("Guerreiro1 - Ataque: %i - Defesa: %i - Carisma: %i - PV: %i\n", guerreiro1.ataque, guerreiro1.defesa, guerreiro1.carisma, guerreiro1.pontos_vida);
    printf("Guerreiro2 - Ataque: %i - Defesa: %i - Carisma: %i - PV: %i\n", guerreiro2.ataque, guerreiro2.defesa, guerreiro2.carisma, guerreiro2.pontos_vida);

    do {
        if (atacante == 1) {
            ataque(&guerreiro1, &guerreiro2);
            atacante = 2;
        } else {
            ataque(&guerreiro2, &guerreiro1);
            atacante = 1;
        }
    } while (guerreiro1.pontos_vida > 0 && guerreiro2.pontos_vida > 0);

    if (guerreiro1.pontos_vida > 0) {
        printf("\nVencedor: %i", guerreiro1.id_guerreiro);
        printf("\nPontos de vida restantes: %i", guerreiro1.pontos_vida);
    } 

    if (guerreiro2.pontos_vida > 0) {
        printf("\nVencedor: %i", guerreiro2.id_guerreiro);
        printf("\nPontos de vida restantes: %i", guerreiro2.pontos_vida);
    } 
}

int main () {
    srand(1);
    jogo();
}