#include "Livro.hpp"
#include "ExcecaoBiblioteca.hpp"

void Livro::emprestar(std::string usuario) {
    if (!_disponivel) {
        throw biblioteca_excp::ExcecaoLivroIndisponivel(_titulo);
    }

    _disponivel = false;
    _emprestado_para = usuario;
}

void Livro::devolver() {
    if (_disponivel) {
        throw biblioteca_excp::ExcecaoLivroIndisponivel(_titulo);
    }

    _disponivel = true;
    _emprestado_para = "";
}

bool Livro::estaDisponivel() {
    return _disponivel;
}
