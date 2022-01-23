#include <iostream>

#include "Agenda.h"
#include "Amigo.h"
#include "Conhecido.h"

enum Identifier {
    IAmigo = 1,
    IConhecido = 2
};

Agenda::~Agenda() { 
    unsigned int size = pessoas.size(), i = 0;
    for (i = 0; i < size; i++) {
        delete pessoas[i];
    }
}

Agenda::Agenda(unsigned int n) {
    unsigned int i = 0;
    for (i = 0; i < n; i++) {
        unsigned int r = (rand() % 2) + 1;
        if (r == Identifier::IAmigo) {
            amigos_count++;
            pessoas.push_back(new Amigo());
        } else if (r == Identifier::IConhecido) {
            conhecidos_count++;
            pessoas.push_back(new Conhecido());
        }
    }
}

void Agenda::imprimeAniversarios() {
    for (auto& p : pessoas) {
        Amigo *a = dynamic_cast<Amigo *>(p);
        if (a) {
            std::cout << a->getBirthday() << std::endl;
        }
    }
}

void Agenda::imprimeEmails() {
    for (auto& p : pessoas) {
        Conhecido *c = dynamic_cast<Conhecido *>(p);
        if (c) {
            std::cout << c->getEmail() << std::endl;
        }
    }
}


void Agenda::addInformacoes() {
    for (auto& p : pessoas) {
        Conhecido *c = dynamic_cast<Conhecido *>(p);
        if (c) {
            std::string email;
            std::cout << "Email: ";
            std::cin >> email;
            c->setEmail(email);
        } else {
            Amigo *a = dynamic_cast<Amigo *>(p);
            if (a) {
                std::string birthday;
                std::cout << "Aniversario (DD/MM/AAAA): ";
                std::cin >> birthday;
                a->setBirthday(birthday);
            }
        }
    }
}