#ifndef FIGURA_H
#define FIGURA_H

#include <iostream>
#include "Ponto.hpp"

using namespace std;

class Figura {
public:
    virtual bool contem(Ponto p) const = 0;
    virtual ~Figura() {
        std::cout << "Destrutor Figura" << std::endl;
    }
    friend Figura* operator+(Figura& f1, Figura& f2);
    friend Figura* operator-(Figura& f1, Figura& f2);
};

class FiguraComposta : public Figura {
    private:
        Figura* _figura1;
        Figura* _figura2;
        char _tipo;

    public:
        FiguraComposta(Figura* f1, Figura* f2, char tipo) : _figura1(f1), _figura2(f2), _tipo(tipo) {}

        bool contem(Ponto p) const;

        ~FiguraComposta() {
            std::cout << "Destrutor FiguraComposta" << std::endl;
        }
};

#endif