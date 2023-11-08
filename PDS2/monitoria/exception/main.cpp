#include <iostream>
#include "Biblioteca.hpp"

void casoDeTeste1(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Dom Casmurro");
    biblioteca.adicionarLivro("Grande Sertão: Veredas");
    biblioteca.listarLivros();
}

void casoDeTeste2(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Dom Casmurro");
    biblioteca.emprestarLivro("Dom Casmurro", "UsuarioA");
    biblioteca.devolverLivro("Dom Casmurro", "UsuarioA");
    biblioteca.listarLivros();
}

void casoDeTeste3(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Grande Sertão: Veredas");
    try {
        biblioteca.emprestarLivro("Memorias Postumas de Bras Cubas", "UsuarioB");
    } catch (biblioteca_excp::ExcecaoLivroIndisponivel& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

void casoDeTeste4(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Grande Sertão: Veredas");
    try {
        biblioteca.devolverLivro("Grande Sertão: Veredas", "UsuarioB");
    } catch (biblioteca_excp::ExcecaoDevolucaoNaoAutorizada& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

void casoDeTeste5(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Memorias Postumas de Bras Cubas");
    biblioteca.emprestarLivro("Memorias Postumas de Bras Cubas", "UsuarioC");
    try {
        biblioteca.devolverLivro("Memorias Postumas de Bras Cubas", "UsuarioB");
    } catch (biblioteca_excp::ExcecaoDevolucaoNaoAutorizada& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

void casoDeTeste6(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Dom Casmurro");
    biblioteca.emprestarLivro("Dom Casmurro", "UsuarioA");
    try {
        biblioteca.devolverLivro("Memorias Postumas de Bras Cubas", "UsuarioA");
    } catch (biblioteca_excp::ExcecaoDevolucaoNaoAutorizada& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

void casoDeTeste7(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Dom Casmurro");
    biblioteca.emprestarLivro("Dom Casmurro", "UsuarioA");
    try {
       biblioteca.emprestarLivro("Dom Casmurro", "UsuarioB");
    } catch (biblioteca_excp::ExcecaoLivroIndisponivel& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

void casoDeTeste8(Biblioteca& biblioteca) {
    biblioteca.adicionarLivro("Dom Casmurro");
    biblioteca.adicionarLivro("Memorias Postumas de Bras Cubas");
    biblioteca.emprestarLivro("Dom Casmurro", "UsuarioA");
    biblioteca.emprestarLivro("Memorias Postumas de Bras Cubas", "UsuarioB");
    biblioteca.listarLivros();
    try {
       biblioteca.emprestarLivro("Dom Casmurro", "UsuarioC");
    } catch (biblioteca_excp::ExcecaoLivroIndisponivel& e) {
        std::cout << e.what() << std::endl;
    }

    try {
       biblioteca.devolverLivro("Memorias Postumas de Bras Cubas", "UsuarioB");
    } catch (biblioteca_excp::ExcecaoLivroIndisponivel& e) {
        std::cout << e.what() << std::endl;
    }
    biblioteca.listarLivros();
}

int main() {
    Biblioteca biblioteca;

    int escolha;
    std::cin >> escolha;

    switch (escolha) {
    case 1:
        casoDeTeste1(biblioteca);
        break;
    case 2:
        casoDeTeste2(biblioteca);
        break;
    case 3:
        casoDeTeste3(biblioteca);
        break;
    case 4:
        casoDeTeste4(biblioteca);
        break;
    case 5:
        casoDeTeste5(biblioteca);
        break;
    case 6:
        casoDeTeste6(biblioteca);
        break;
    case 7:
        casoDeTeste7(biblioteca);
        break;
    case 8:
        casoDeTeste8(biblioteca);
        break;
    default:
        break;
    }

    return 0;
}
