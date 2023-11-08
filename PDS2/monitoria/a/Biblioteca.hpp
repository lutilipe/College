#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <iostream>
#include <vector> 
#include "Livro.hpp" 

using namespace std;

class Biblioteca {
private:
vector<Livro*> _livros; // composição 

public:
    Biblioteca();
    ~Biblioteca();
    void add_livro(Livro* livro); 
    void list_livros();
    void find_livro(int id);
    void remove_livro(int id);
};

#endif
