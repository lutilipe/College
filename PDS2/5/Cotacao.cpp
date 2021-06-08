#include <string>

#include "Cotacao.hpp"

Cotacao::Cotacao() {
    _data = "";
    _valor = 0.0;
}

Cotacao::Cotacao(std::string data, double valor) {
    _data = data;
    _valor = valor;
}

std::string Cotacao::get_data() {
    return _data;
}

void Cotacao::set_data(std::string data) {
    _data = data;
}

double Cotacao::get_valor() {
    return _valor;
}

void Cotacao::set_valor(double valor) {
    _valor = valor;
}