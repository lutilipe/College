#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <string>
#include <map>
#include <iostream>
#include "Livro.hpp"
#include "ExcecaoBiblioteca.hpp"

class Biblioteca {
public:
    void adicionarLivro(std::string titulo);
    void emprestarLivro(std::string titulo, std::string usuario);
    void devolverLivro(std::string titulo, std::string usuario);
    void listarLivros();

private:
    std::map<std::string, Livro*> livros;
};

#endif
