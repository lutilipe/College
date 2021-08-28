#include <iostream>
#include "arranjo.h"

using std::cin;
using std::cout; 
using std::endl;

int main() {
  try { 
    int inicio, fim;
    cin >> inicio >> fim;
    Arranjo<double> arranjo(inicio, fim);
    char opcao;
    while (cin >> opcao) {
      int indice;
      int valor;
      if (opcao == 'a') {
        cin >> indice;
        cin >> valor;
        arranjo.atribuir(indice, valor);
      } else if (opcao == 'v') {
        cin >> indice;
        valor = arranjo.valor(indice);
        cout << valor << endl;
      } else if (opcao == 'f') {
        return 0;
      } else {
        cout << "Opção inválida!" << endl;
      }
    }
  } catch (ExcecaoIntervaloVazio e) {
    cout << "Erro: intervalo [" << e.inicio << ", " << e.fim << "]" 
         << " é vazio." << endl;
  } catch (ExcecaoIndiceNaoInicializado e) {
    cout << "Erro: índice " << e.indice << " não foi inicializado." << endl;
  } catch (ExcecaoIndiceInvalido e) {
    cout << "Erro: índice " << e.indice << " não pertence ao intervalo ["
     << e.inicio << ", " << e.fim << "]." << endl;
  } catch (...) {
    cout << "Erro desconhecido!" << endl;
  }
  return 0;
}