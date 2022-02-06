#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

#include <iostream>
#include <vector>

#include "Professor.h"

class Universidade {
    private:
        std::vector<Professor*> professores;

    public:
        Universidade() {};
        double totalPago();
        void addProfessor(Professor& p);
        virtual ~Universidade() {};
};

double Universidade::totalPago() {
    double total = 0;
    std::cout << "Nome\t" << "Salario" << std::endl;
    for (auto p : professores) {
        double s = p->getSalario();
        std::cout << p->getName() << "\t" << s << std::endl;
        total += s;
    }
    std::cout << "Total:\t" << total << std::endl;
    return total;
}

void Universidade::addProfessor(Professor& p) {
    professores.push_back(&p);
}

#endif