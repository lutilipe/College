#include <string>
#include "ContadorDePalavras.hpp"
#include "Palavra.hpp"
#include <iostream>

ContadorDePalavras::ContadorDePalavras() {}

void ContadorDePalavras::Adicionar(std::string p) {
    for (auto &palavra : _lista_de_palavras) {
        if (palavra.palavra() == p) {
            palavra.Incrementar();
            return;
        }
    }
    Palavra w(p);
    _lista_de_palavras.push_back(w);
}

void ContadorDePalavras::ImprimirOrdenado() {
    _lista_de_palavras.sort();
    for (auto &palavra : _lista_de_palavras) {
        std::cout << palavra.palavra() << " " << palavra.ocorrencias() << std::endl;
    }
}   