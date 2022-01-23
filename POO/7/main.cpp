#include <ctime>
#include <iostream>

#include "Agenda.h"

int main() {
    srand((unsigned int) time (NULL));

    int n = 0;
    std::cin >> n;
    Agenda a(n);

    std::cout << a.getAmigosCount() << std::endl;
    std::cout << a.getConhecidosCount() << std::endl;

    a.addInformacoes();

    a.imprimeAniversarios();
    a.imprimeEmails();

    return 0;
}