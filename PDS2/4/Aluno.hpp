#ifndef ALUNO_H
#define ALUNO_H

#include <iostream>

struct Aluno {
    int matricula;
    std::string nome;

    Aluno();
    Aluno(int matricula, std::string nome);
    int getMatricula();
    void setMatricula(int matricula);
    std::string getNome();
    void setNome(std::string nome);
    void imprimir_dados();
};

#endif