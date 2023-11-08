#include <iostream>
#include "LivroInfantil.hpp"
#include <string>
using namespace std;

LivroInfantil::LivroInfantil(string titulo, string autor, int anoPublicacao, int faixaEtariaMinima ) : Livro(titulo, autor, anoPublicacao) {
  _faixaEtariaMinima = faixaEtariaMinima;
  _genero = "Infantil"; // Agora _genero é acessível
};

LivroInfantil::~LivroInfantil() {
    cout << "Destrutor LivroInfantil" << endl;
};

void LivroInfantil::print_info() {
  Livro::print_info();
  cout << "\tFaixa etaria minima: " << _faixaEtariaMinima << endl;
};

int LivroInfantil::getId() const {
    return _id;
};
