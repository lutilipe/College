#include <iostream>
#include <string>
#include <vector>
#include "ContaBancaria.hpp"
#include "Banco.hpp"


int main() {
    Banco meuBanco;

    ContaBancaria* conta1 = new ContaBancaria();
    conta1->titular = "Joao";
    conta1->saldo = 1500;

    ContaBancaria* conta2 = new ContaBancaria();
    conta2->titular = "Maria";
    conta2->saldo = 1000;

    ContaBancaria* conta3 = new ContaBancaria();
    conta3->titular = "Luiz";
    conta3->saldo = 3000;

    ContaBancaria* conta4 = new ContaBancaria();
    conta4->titular = "Lara";
    conta4->saldo = 2000;

    ContaBancaria* conta5 = new ContaBancaria();
    conta5->titular = "Luisa";
    conta5->saldo = 5000;

    meuBanco.adicionarConta(conta1);
    meuBanco.adicionarConta(conta2);
    meuBanco.adicionarConta(conta3);
    meuBanco.adicionarConta(conta4);
    meuBanco.adicionarConta(conta5);

    meuBanco.exibirTodasContas();

    conta1->depositar(500);
    conta2->sacar(200);
    conta3->sacar(100);
    conta4->depositar(-1);
    conta5->sacar(5001);

    meuBanco.exibirTodasContas();

    conta1->sacar(500);
    conta2->depositar(200);
    conta3->depositar(100);
    conta4->sacar(300);
    conta5->depositar(50);

    meuBanco.exibirTodasContas();

    return 0;
}
