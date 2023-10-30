#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ConversorMoedas.hpp"

TEST_CASE("ConversorMoedas - Definir e Verificar Taxa de Câmbio") {
    ConversorMoedas conversor;
    conversor.definirTaxaCambio("USD", "EUR", 0.85);
    CHECK(conversor.possuiTaxaCambio("USD", "EUR") == true);
}

TEST_CASE("ConversorMoedas - Conversão de Moedas") {
    ConversorMoedas conversor;
    conversor.definirTaxaCambio("USD", "EUR", 0.85);
    double valorConvertido = conversor.converter("USD", "EUR", 100.0);
    CHECK(valorConvertido == doctest::Approx(85.0));
}

TEST_CASE("ConversorMoedas - Remover Taxa de Câmbio") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.definirTaxaCambio("YYY", "ZZZ", 0.85), cexc::moeda_invalida);
}
