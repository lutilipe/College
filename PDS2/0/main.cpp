#include <iostream>
#include <chrono>
#include <thread>

#include "jogo_da_vida.h"

using std::cin;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;  // Para a execução por x ms;
using namespace std::chrono_literals;  // Necessário para poder escrever, e.g. 100ms.

void Imprimir(const Torus& t) {
  cout << "  "; 
  for (int i = 0; i < t.numero_de_colunas; ++i) {
    cout << "- "; 
  }
  cout << endl;
  for (int i = 0; i < t.numero_de_linhas; ++i) {
    cout << "| ";
    for (int j = 0; j < t.numero_de_colunas; ++j) {
      if (t.viva[i][j]) {
        cout << "* "; 
      } else {
        cout << "  ";
      }
    }
    cout << "|" << endl;
  }
  cout << "  "; 
  for (int i = 0; i < t.numero_de_colunas; ++i) {
    cout << "- "; 
  }
  cout << endl;
}


int main() {
  // Incializa o torus com os dados do arquivo.
  int numero_de_iteracao;
  cin >> numero_de_iteracao;    

  int numero_de_linhas;
  cin >> numero_de_linhas;
  int numero_de_colunas;
  cin >> numero_de_colunas;

  Torus torus;
  Inicializar(numero_de_linhas, numero_de_colunas, torus);
  int linha = 0, coluna = 0;
  while (cin >> linha >> coluna) {
    torus.viva[linha][coluna] = true;
  } 
  Imprimir(torus);
  
  // Executa o número esperado de iterações.
 /*  for (int i = 0; i <= numero_de_iteracao; i++) {
    ExecutarUmaIteracao(torus);
    Imprimir(torus);
    sleep_for(100ms);
  } */
  return 0;
}