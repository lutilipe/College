#ifndef PROFINTEGRAL_H
#define PROFINTEGRAL_H

#include <string>
#include "Professor.h"

class ProfIntegral: public Professor {
        double salarioMensal;
    public:
       ProfIntegral(std::string n, double sm): Professor(n), salarioMensal(sm) {};
       double getSalario();
       virtual ~ProfIntegral() {}
};

inline double ProfIntegral::getSalario() { return salarioMensal; }

#endif