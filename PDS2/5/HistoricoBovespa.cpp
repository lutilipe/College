#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <iostream>

#include "Cotacao.hpp"
#include "HistoricoBovespa.hpp"

HistoricoBovespa::HistoricoBovespa() {}

void HistoricoBovespa::inserir_cotacao(std::string sigla, std::string data, double valor) {
    Cotacao *cotacao = new Cotacao(data, valor);
    _cotacoes[sigla].push_back(*cotacao);
}

double HistoricoBovespa::calcular_valor_medio_acao(std::string sigla) {
    double total = 0.0;
    for (Cotacao &c : _cotacoes[sigla]) {
        total += c.get_valor();
    }
    return total / _cotacoes[sigla].size();
}

Cotacao* HistoricoBovespa::recuperar_cotacao_maxima_acao(std::string sigla) {
    if (_cotacoes[sigla].size() == 0) return nullptr;
    double max_value = std::numeric_limits<double>::lowest();
    Cotacao *max_c;
    for (Cotacao &c : _cotacoes[sigla]) {
        if (c.get_valor() > max_value) {
            max_value = c.get_valor();
            max_c = &c;
        } 
    }
    return max_c;
}

Cotacao* HistoricoBovespa::recuperar_cotacao_minima_acao(std::string sigla) {
    if (_cotacoes[sigla].size() == 0) return nullptr;
    double min_value = std::numeric_limits<double>::max();
    Cotacao *min_c;
    for (Cotacao &c : _cotacoes[sigla]) {
        if (c.get_valor() < min_value) {
            min_value = c.get_valor();
            min_c = &c;
        } 
    }
    return min_c;
}

void HistoricoBovespa::imprimir_estatisticas_completas() {
    for (auto const &s : _cotacoes) {
        std::cout << s.first << " ";
        for (Cotacao i : s.second) {
            std::cout << i.get_valor() << " ";
        }
        std::cout << "| ";
        std::cout << recuperar_cotacao_minima_acao(s.first)->get_valor() << " ";
        std::cout << recuperar_cotacao_maxima_acao(s.first)->get_valor() << " ";
        std::cout << calcular_valor_medio_acao(s.first);
        std::cout << std::endl;
    }
}