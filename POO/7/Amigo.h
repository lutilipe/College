#ifndef AMIGO_H
#define AMIGO_H

#include <string>

#include "Pessoa.h"

class Amigo: public Pessoa {
    public:
        Amigo(): birthday("indefinido") {};
        std::string getBirthday();
        void setBirthday(std::string b);
    
    private:
        std::string birthday;
};

inline std::string Amigo::getBirthday() { return birthday; }
inline void Amigo::setBirthday(std::string b) { birthday = b; }

#endif