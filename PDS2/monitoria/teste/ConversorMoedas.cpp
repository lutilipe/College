#include "ConversorMoedas.hpp"

void ConversorMoedas::definirTaxaCambio(std::string de, std::string para, double taxa) {
    taxasCambio[std::make_pair(de, para)] = taxa;
    taxasCambio[std::make_pair(para, de)] = 1.0 / taxa;
}

double ConversorMoedas::converter(std::string de, std::string para, double valor) {
    auto it = taxasCambio.find(std::make_pair(de, para));
    double taxa = it->second;
    return valor * taxa;
}

bool ConversorMoedas::possuiTaxaCambio(std::string de, std::string para) {
    auto it = taxasCambio.find(std::make_pair(de, para));
    return it != taxasCambio.end();
}
