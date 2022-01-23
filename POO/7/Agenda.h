#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>

#include "Pessoa.h"

class Agenda {
    public:
        Agenda(unsigned int n = 0);
        ~Agenda();

        std::vector<Pessoa*> getPessoas();
        unsigned int getAmigosCount();
        unsigned int getConhecidosCount();

        void imprimeAniversarios();
        void imprimeEmails();
        void addInformacoes();
    
    private:
        std::vector<Pessoa*> pessoas;
        unsigned int amigos_count = 0;
        unsigned int conhecidos_count = 0;
};

inline std::vector<Pessoa*> Agenda::getPessoas() { return pessoas; }
inline unsigned int Agenda::getConhecidosCount() { return conhecidos_count; }
inline unsigned int Agenda::getAmigosCount() { return amigos_count; }

#endif