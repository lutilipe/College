#include "ConversorMoedas.hpp"

void ConversorMoedas::definirTaxaCambio(std::string de, std::string para, double taxa) {
    if (taxa < 0) {
        throw cexc::valor_invalido();
    }
    if (!checarMoedaValida(de) || !checarMoedaValida(para)) {
        throw cexc::moeda_invalida();
    }
    std::string k = de + para;
    taxasCambio[k] = taxa;
}

double ConversorMoedas::converter(std::string de, std::string para, double valor) {
    if (valor < 0) {
        throw cexc::valor_invalido();
    }
    std::string k = de + para;
    auto it = taxasCambio.find(k);
    if (it != taxasCambio.end()) {
        double taxa = it->second;
        return valor * taxa;
    }
    throw cexc::conversao_inexistente();
}

bool ConversorMoedas::possuiTaxaCambio(std::string de, std::string para) {
    std::string k = de + para;
    auto it = taxasCambio.find(k);
    return it != taxasCambio.end();
}

bool ConversorMoedas::checarMoedaValida(std::string moeda) {
    for (int i = 0; i < MOEDAS_VALIDAS.size(); i++) {
        if (MOEDAS_VALIDAS[i] == moeda) {
            return true;
        }
    }
    return false;
}