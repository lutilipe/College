#include <iostream>
#include <iomanip>
#include <string>

#include "Cotacao.hpp"
#include "HistoricoBovespa.hpp"

void avaliacao_basica() {
    
    HistoricoBovespa historico;

    historico.inserir_cotacao("XYZ", "01/01/2020", 10.0);
    historico.inserir_cotacao("XYZ", "02/02/2020", 20.0);
    historico.inserir_cotacao("XYZ", "03/03/2020", 30.0);

    historico.inserir_cotacao("ABC", "04/04/2020", 40.0);

    std::cout << std::fixed << std::showpoint; 
    std::cout << std::setprecision(2);

    // XYZ
    Cotacao* min1 = historico.recuperar_cotacao_minima_acao("XYZ");
    Cotacao* max1 = historico.recuperar_cotacao_maxima_acao("XYZ");
    double avg1 = historico.calcular_valor_medio_acao("XYZ");
    std::cout << "XYZ" << " " << avg1 << std::endl;
    std::cout << min1->get_data() << " " << min1->get_valor() << " " << max1->get_data() << " " << max1->get_valor() << std::endl;

    // ABC
    Cotacao* min2 = historico.recuperar_cotacao_minima_acao("ABC");
    Cotacao* max2 = historico.recuperar_cotacao_maxima_acao("ABC");
    double avg2 = historico.calcular_valor_medio_acao("ABC");
    std::cout << "ABC" << " " << avg2 << std::endl;
    std::cout << min2->get_data() << " " << min2->get_valor() << " " << max2->get_data() << " " << max2->get_valor() << std::endl;

    std::cout << "---------------" << std::endl;

    historico.imprimir_estatisticas_completas();
}

int main() {
  
    // NÃO ALTERE ESSA LINHA
    avaliacao_basica();

    HistoricoBovespa historico;
    double valor;
    std::string data, sigla;

    while (std::cin >> sigla >> data >> valor) {
        historico.inserir_cotacao(sigla, data, valor);
    }

    historico.imprimir_estatisticas_completas();

    return 0;
}