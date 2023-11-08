#include "Livro.hpp"
#include <iostream>
#include <string>
using namespace std;

int Livro::_prox_id = 1; // Inicialização da variável estática _prox_id

  Livro::Livro(string titulo, string autor, int anoPublicacao) {
    _id = _prox_id++;
    _titulo = titulo;
    _autor = autor;
    _anoPublicacao = anoPublicacao;
    _genero = "Livro"; // Gênero padrão
};

Livro::~Livro() {
    cout << "Destrutor Livro" << endl;
};

void Livro::print_info() {
    cout << "Info: Livro " << _id << endl;
    cout << "\tTitulo: " << _titulo << endl;
    cout << "\tAutor: " << _autor << endl;
    cout << "\tAno de publicacao: " << _anoPublicacao << endl;
    cout << "\tGenero: " << _genero << endl;
};

int Livro::getId() const {
    return _id;
};
