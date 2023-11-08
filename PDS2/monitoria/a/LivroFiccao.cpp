#include "LivroFiccao.hpp"
#include <iostream>
#include <string>
using namespace std;

LivroFiccao::LivroFiccao(string titulo, string autor, int anoPublicacao, string subgenero) : Livro(titulo, autor, anoPublicacao) {
    _subgenero = subgenero;
    _genero = "Ficcao"; // Agora _genero é acessível
};


LivroFiccao::~LivroFiccao() {
    cout << "Destrutor LivroFiccao" << endl;
};

void LivroFiccao::print_info() {
    Livro::print_info(); // Chama o método da classe base
    cout << "\tSubgenero: " << _subgenero << endl;
};

int LivroFiccao::getId() const {
    return _id;
};

