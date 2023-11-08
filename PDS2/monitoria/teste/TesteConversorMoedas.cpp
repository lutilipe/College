#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ConversorMoedas.hpp"

TEST_CASE("ConversorMoedas - Definir e Verificar Taxa de Câmbio") {
    ConversorMoedas conversor;
    conversor.definirTaxaCambio("USD", "EUR", 0.85);
    CHECK(conversor.possuiTaxaCambio("USD", "EUR") == true);
}

TEST_CASE("ConversorMoedas - Definir e Verificar Taxa de Câmbio") {
    ConversorMoedas conversor;
    CHECK(conversor.possuiTaxaCambio("USD", "EUR") == false);
}

TEST_CASE("ConversorMoedas - Conversão de Moedas") {
    ConversorMoedas conversor;
    conversor.definirTaxaCambio("USD", "EUR", 0.85);
    double valorConvertido = conversor.converter("USD", "EUR", 100.0);
    CHECK(valorConvertido == doctest::Approx(85.0));
}

TEST_CASE("ConversorMoedas - Moeda invalida Ambas") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.definirTaxaCambio("YYY", "ZZZ", 0.85), cexc::moeda_invalida);
}

TEST_CASE("ConversorMoedas - Moeda invalida 2") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.definirTaxaCambio("BRL", "ZZZ", 0.85), cexc::moeda_invalida);
}

TEST_CASE("ConversorMoedas - Moeda invalida 1") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.definirTaxaCambio("YYY", "BRL", 0.85), cexc::moeda_invalida);
}

TEST_CASE("ConversorMoedas - Valor invalido definicao") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.definirTaxaCambio("BRL", "USD", -1), cexc::valor_invalido);
}

TEST_CASE("ConversorMoedas - Valor invalido converter") {
    ConversorMoedas conversor;
    conversor.definirTaxaCambio("USD", "EUR", 0.85);
    CHECK_THROWS_AS(conversor.converter("USD", "EUR", -1), cexc::valor_invalido);
}

TEST_CASE("ConversorMoedas - Conversao inexistente") {
    ConversorMoedas conversor;
    CHECK_THROWS_AS(conversor.converter("USD", "EUR", 2), cexc::conversao_inexistente);
}

TEST_CASE("ConversorMoedas - Checar moeda valida") {
    ConversorMoedas conversor;
    CHECK(conversor.checarMoedaValida("USD") == true);
}