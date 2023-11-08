#include <iostream>
#include "LivroNaoFiccao.hpp"
#include <string>

using namespace std;

LivroNaoFiccao::LivroNaoFiccao(string titulo, string autor, int anoPublicacao, string assunto) : Livro(titulo, autor, anoPublicacao) {
  _assunto = assunto;
  _genero = "NaoFiccao";
};

LivroNaoFiccao::~LivroNaoFiccao() {
    cout << "Destrutor LivroNaoFiccao" << endl;
};
void LivroNaoFiccao::print_info() {
Livro::print_info();
  cout << "\tAssunto: " << _assunto << endl;
};
int LivroNaoFiccao::getId() const {
    return _id;
};