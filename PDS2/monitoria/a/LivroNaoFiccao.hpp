#ifndef LIVRONAOFICCAO_HPP
#define LIVRONAOFICCAO_HPP

#include <iostream>
#include "Livro.hpp"
#include <string>
using namespace std;

class LivroNaoFiccao : public Livro {
private:
string _assunto;

public:
LivroNaoFiccao(string titulo, string autor, int anoPublicacao, string assunto);
virtual ~LivroNaoFiccao();
virtual void print_info();
int getId() const;

};
#endif