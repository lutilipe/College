#ifndef LIVROFCCAO_H
#define LIVROFCCAO_H
#include "Livro.hpp"
#include <iostream>
#include <string>
using namespace std;

class LivroFiccao : public Livro{
private:
string _subgenero;

public:
LivroFiccao(string titulo, string autor, int anoPublicacao, string subgenero);
virtual ~LivroFiccao();
virtual void print_info();
 int getId() const;
};
#endif