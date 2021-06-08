#include "jogo_da_vida.h"

void Inicializar(int l, int c, Torus &t) {
    int i = 0, j = 0;
    for (i = 0; i < l; i++) {
        for (j = 0; j < l; j++) {
            t.viva[i][j] = 0;
        }
    }
}

void ExecutarUmaIteracao(Torus& t) {
}
