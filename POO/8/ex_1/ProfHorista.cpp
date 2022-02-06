#ifndef PROFHORISTA_H
#define PROFHORISTA_H

#include <string>
#include "Professor.h"

class ProfHorista: public Professor {
        double nrNorasTrabalhadas;
        double valorHora;
    public:
        ProfHorista(std::string n, double nht, double vh): Professor(n), nrNorasTrabalhadas(nht), valorHora(vh) {};
        double getSalario();
        virtual ~ProfHorista() {};
};

inline double ProfHorista::getSalario() { return nrNorasTrabalhadas * valorHora; }

#endif