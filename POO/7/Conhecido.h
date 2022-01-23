#ifndef CONHECIDO_H
#define CONHECIDO_H

#include <string>

#include "Pessoa.h"

class Conhecido: public Pessoa {
    public:
        Conhecido(): email("indefinido") {};
        std::string getEmail();
        void setEmail(std::string e);
    
    private:
        std::string email;
};

inline std::string Conhecido::getEmail() { return email; }
inline void Conhecido::setEmail(std::string e) { email = e; }

#endif