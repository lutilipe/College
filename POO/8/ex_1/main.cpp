#include <iostream>
#include <string>
#include "ProfHorista.cpp"
#include "ProfIntegral.cpp"
#include "Universidade.cpp"

int main() {
    ProfHorista p1("Luiz", 8, 30);
    ProfHorista p2("Caio", 4, 15);
    ProfIntegral p3("Joao", 80);

    Universidade u;

    u.addProfessor(p1);
    u.addProfessor(p2);
    u.addProfessor(p3);

    u.totalPago();
    return 0;
}