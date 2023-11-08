#include "Biblioteca.hpp"

void Biblioteca::adicionarLivro(std::string titulo) {
    Livro* novoLivro = new Livro(titulo);
    livros[titulo] = novoLivro;
}

void Biblioteca::emprestarLivro(std::string titulo, std::string usuario) {
    if (livros.count(titulo) > 0) {
        Livro* livro = livros[titulo];
        if (livro->estaDisponivel()) {
            livro->emprestar(usuario);
            return;
        }
    }
    throw biblioteca_excp::ExcecaoLivroIndisponivel(titulo);
}

void Biblioteca::devolverLivro(std::string titulo, std::string usuario) {
    if (livros.count(titulo) > 0) {
        Livro* livro = livros[titulo];
        if (!livro->estaDisponivel() && livro->getEmprestadoPara() == usuario) {
            livro->devolver();
            return;
        }
    }
    throw biblioteca_excp::ExcecaoDevolucaoNaoAutorizada(titulo, usuario);
}

void Biblioteca::listarLivros() {
    std::cout << "Livros na Biblioteca:" << std::endl;
    for (auto pair : livros) {
        Livro* livro = pair.second;
        std::cout << livro->getTitulo() << " - " << (livro->estaDisponivel() ? "Disponível" : "Indisponível") << std::endl;
    }
}
