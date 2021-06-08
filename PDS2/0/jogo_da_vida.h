#pragma once 

// Representa na memória um Torus:
// https://pt.wikipedia.org/wiki/Toro_(topologia)
struct Torus {
  bool viva[100][100];  // Armazena o estado das células.
  int numero_de_linhas;  // Número de linhas no torus. 
  int numero_de_colunas;  // Número de colunas no torus.
};

// Inicializa um torus com l linhas e c colunas.
// Todas as células são inicializadas como mortas.
void Inicializar(int l, int c, Torus& t);

// Atualiza o torus para próxima iteração do jogo da vida.
void ExecutarUmaIteracao(Torus& t);