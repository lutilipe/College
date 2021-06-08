#ifndef HISTORICO_BOVESPA_H
#define HISTORICO_BOVESPA_H

#include <string>
#include <map>
#include <vector>

#include "Cotacao.hpp"

struct HistoricoBovespa {
    std::map<std::string, std::vector<Cotacao>> _cotacoes;

    HistoricoBovespa();
    void inserir_cotacao(std::string sigla, std::string data, double valor);
    double calcular_valor_medio_acao(std::string sigla);
    Cotacao* recuperar_cotacao_maxima_acao(std::string sigla);
    Cotacao* recuperar_cotacao_minima_acao(std::string sigla);
    void imprimir_estatisticas_completas();
};

#endif