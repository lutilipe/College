#ifndef CONVERSOR_MOEDAS_H
#define CONVERSOR_MOEDAS_H

#include <string>
#include <map>
#include <utility>
#include <vector>

namespace cexc {
    class valor_invalido {};
    class moeda_invalida {};
    class conversao_inexistente {};
}

class ConversorMoedas {
    public:
        void definirTaxaCambio(std::string de, std::string para, double taxa);
        double converter(std::string de, std::string para, double valor);
        bool possuiTaxaCambio(std::string de, std::string para);
        bool checarMoedaValida(std::string moeda);

    private:
        std::map<std::string, double> taxasCambio;
        std::vector<std::string> MOEDAS_VALIDAS = {
            "USD", // Dólar dos Estados Unidos
            "EUR", // Euro
            "JPY", // Iene Japonês
            "GBP", // Libra Esterlina (Reino Unido)
            "CAD", // Dólar Canadense
            "AUD", // Dólar Australiano
            "CHF", // Franco Suíço
            "CNY", // Yuan Chinês
            "INR", // Rúpia Indiana
            "BRL"  // Real Brasileiro
        };
};

#endif