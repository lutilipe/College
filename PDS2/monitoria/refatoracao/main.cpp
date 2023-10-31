#include <iostream>
#include <string>
#include <vector>
#include "ContaBancaria.hpp"
#include "ContaPoupanca.hpp"
#include "ContaCorrente.hpp"
#include "Banco.hpp"


int main() {
    Banco meuBanco;

    conta_corrente* conta1 = new conta_corrente();
    conta1->titular = "Joao";
    conta1->saldo = 1500;
    conta1->limiteChequeEspecial = 200;

    conta_poupanca* conta2 = new conta_poupanca();
    conta2->titular = "Maria";
    conta2->saldo = 1000;
    conta2->taxaJuros = 2.0;

    conta_poupanca* conta3 = new conta_poupanca();
    conta3->titular = "Luiz";
    conta3->saldo = 3000;
    conta3->taxaJuros = 1.5;

    conta_poupanca* conta4 = new conta_poupanca();
    conta4->titular = "Lara";
    conta4->saldo = 2000;
    conta4->taxaJuros = 2.5;

    conta_corrente* conta5 = new conta_corrente();
    conta5->titular = "Luisa";
    conta5->saldo = 5000;
    conta5->limiteChequeEspecial = 300;

    meuBanco.adicionarConta(conta1);
    meuBanco.adicionarConta(conta2);
    meuBanco.adicionarConta(conta3);
    meuBanco.adicionarConta(conta4);
    meuBanco.adicionarConta(conta5);

    meuBanco.exibir_todas_contas();

    conta1->depositar(500);
    conta2->sacar(200);
    conta3->sacar(100);
    conta4->depositar(-1);
    conta5->sacar(5001);

    meuBanco.exibir_todas_contas();

    conta1->sacar(500);
    conta2->depositar(200);
    conta3->depositar(100);
    conta4->sacar(300);
    conta5->depositar(50);

    meuBanco.exibir_todas_contas();

    conta1->usarChequeEspecial(500);
    conta2->calcularJuros();
    conta3->calcularJuros();
    conta4->calcularJuros();
    conta5->usarChequeEspecial(50);
    
    meuBanco.exibir_todas_contas();

    return 0;
}
