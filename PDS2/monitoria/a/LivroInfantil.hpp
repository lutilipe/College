#ifndef LIVROINFATIL_HPP
#define LIVROINFATIL_HPP

#include <iostream>
#include "Livro.hpp"
#include <string>
using namespace std;

class LivroInfantil : public Livro {
private:
int _faixaEtariaMinima;

public:
LivroInfantil(string titulo, string autor, int anoPublicacao, int faixaEtariaMinima);
virtual ~LivroInfantil();
virtual void print_info();
 int getId() const;

};
#endif