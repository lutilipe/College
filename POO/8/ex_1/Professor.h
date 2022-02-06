#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>

// Abstract class
class Professor{
        std::string nome;
    public:
        Professor(std::string n): nome(n) {};
        std::string getName() const;
        virtual double getSalario() = 0;
        virtual ~Professor() {};
};

inline std::string Professor::getName() const { return nome; }

#endif