#ifndef LIVRO_H
#define LIVRO_H

#include <iostream>
#include <string>
using namespace std;

class Livro {
private:
static int _prox_id;
string _titulo;
string _autor;
int _anoPublicacao;
protected:
string _genero;
int _id;


public:
Livro(string titulo, string autor, int anoPublicacao);
virtual ~Livro();
virtual void print_info(); 
 int getId() const;
 };
#endif