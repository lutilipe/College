#include "Biblioteca.hpp"
#include "Livro.hpp"
#include "LivroNaoFiccao.hpp"
#include "LivroInfantil.hpp"
#include "LivroFiccao.hpp"
#include <iostream>

using namespace std;

Biblioteca::Biblioteca() {
}

Biblioteca::~Biblioteca() {
    // Destrutor da Biblioteca
        // Se um livro foi removido, chame os destrutores
        for (Livro* livro : _livros) {
            delete livro;
        
    }
    _livros.clear();
}

void Biblioteca::add_livro(Livro* livro) {
    _livros.push_back(livro);
}

void Biblioteca::list_livros() {
    for (Livro* livro : _livros) {
        livro->print_info();
    }
}

void Biblioteca::find_livro(int id) {
    bool encontrado = false;

    for (Livro* livro : _livros) {
        if (livro->getId() == id) {
            livro->print_info();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Erro ao pesquisar: livro com ID " << id << " nao encontrado" << endl;
    }
}

void Biblioteca::remove_livro(int id) {
  bool removido = false;

  for (auto it = _livros.begin(); it != _livros.end(); ) {
      if ((*it)->getId() == id) {
          delete *it; // Chama o destrutor do livro e libera a memória
          _livros.erase(it); // Atualiza o iterador após a remoção
          removido = true;
      } else {
          ++it;
      }
  }


  if (!removido) {
      cout << "Erro ao remover: livro com ID " << id << " nao encontrado" << endl;
  }
}

