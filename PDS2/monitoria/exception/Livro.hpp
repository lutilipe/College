#ifndef LIVRO_H
#define LIVRO_H

#include <string>

class Livro {
public:
    Livro(std::string titulo): _titulo(titulo), _disponivel(true), _emprestado_para("") {};
    void emprestar(std::string usuario);
    void devolver();
    bool estaDisponivel();
    std::string getTitulo() { return _titulo; };
    std::string getEmprestadoPara() { return _emprestado_para; };

private:
    std::string _titulo;
    bool _disponivel;
    std::string _emprestado_para;
};

#endif
