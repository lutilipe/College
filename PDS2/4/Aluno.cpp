#include "Aluno.hpp"
#include <iostream>

Aluno::Aluno() {}

Aluno::Aluno(int m, std::string n) {
    matricula = m;
    nome = n;
}

int Aluno::getMatricula() {
    return matricula;
}

void Aluno::setMatricula(int m) {
    matricula = m;
}

std::string Aluno::getNome() {
    return nome;
}

void Aluno::setNome(std::string n) {
    nome = n;
}

void Aluno::imprimir_dados() {
    std::cout << getMatricula() << ' ' << getNome() << std::endl;
}