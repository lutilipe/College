#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

#include "arranjo.h"

// A classe Arranjo é bastante simples, e só tem dois métodos muito 
// correlacionados. Sendo assim, considera-se a classe como uma única unidade
// de código. 

// Define um tipo qualquer para ser utilizado nos testes.
typedef Arranjo<double> Arranjo_t;

// Define um número qualquer utilizado nos testes de atribuição.
static const double NUMERO = 3.14159;  

TEST_CASE("Atribuição em índices positivos") {
  Arranjo_t arranjo(0, 5);
  for (int i = 0; i <= 5; i++) {
    arranjo.atribuir(i, NUMERO);
  }
  for (int i = 0; i <= 5; i++) {
    CHECK(arranjo.valor(i) == NUMERO);
  }
}

TEST_CASE("Atribuição em índices negativos") {
  Arranjo_t arranjo(-5, 0);
  for (int i = -5; i <= 0; i++) {
    arranjo.atribuir(i, NUMERO);
  }
  for (int i = -5; i <= 0; i++) {
    CHECK(arranjo.valor(i) == NUMERO);
  }
}

TEST_CASE("Atribuição em índices positivos e negativos") {
  Arranjo_t arranjo(-2, 2);
  for (int i = -2; i <= 2; i++) {
    arranjo.atribuir(i, NUMERO);
  }
  for (int i = -2; i <= 2; i++) {
    CHECK(arranjo.valor(i) == NUMERO);
  }
}

TEST_CASE("Atribuição em arranjos unitários") {
  Arranjo_t negativo(-1, -1);
  negativo.atribuir(-1, NUMERO);
  CHECK(negativo.valor(-1) == NUMERO);

  Arranjo_t positivo(1, 1);
  positivo.atribuir(1, NUMERO);
  CHECK(positivo.valor(1) == NUMERO);

  Arranjo_t zero(0, 0);
  zero.atribuir(0, NUMERO);
  CHECK(zero.valor(0) == NUMERO);
}

TEST_CASE("Exceção em Arranjo::Arranjo() quando o intervalo é vazio") {
  CHECK_THROWS_AS(Arranjo_t arranjo(1, -1), ExcecaoIntervaloVazio);
  CHECK_NOTHROW(Arranjo_t arranjo(-1, 1));
  CHECK_NOTHROW(Arranjo_t arranjo(0, 0));  
}

TEST_CASE("Exceção em Arranjo::alterar() quando o índice é inválido") {
  Arranjo_t arranjo(-2, 2);
  CHECK_THROWS_AS(arranjo.atribuir(-3, NUMERO), ExcecaoIndiceInvalido);
  CHECK_THROWS_AS(arranjo.atribuir(3, NUMERO), ExcecaoIndiceInvalido);
}

TEST_CASE("Exceção em Arranjo::valor() quando o índice é inválido") {
  Arranjo_t arranjo(-2, 2);
  CHECK_THROWS_AS(arranjo.valor(-3), ExcecaoIndiceInvalido);
  CHECK_THROWS_AS(arranjo.valor(3), ExcecaoIndiceInvalido);
}

TEST_CASE("Exceção em Arranjo::valor() quando o índice não foi inicializado") {
  Arranjo_t arranjo(-2, 2);
   for (int i = -2; i <= 2; i++) {
    CHECK_THROWS_AS(arranjo.valor(i), ExcecaoIndiceNaoInicializado);
  } 
  for (int i = -2; i <= 2; i++) {
    arranjo.atribuir(i, NUMERO);
  }
  for (int i = -2; i <= 2; i++) {
    CHECK_NOTHROW(arranjo.valor(i));
  }
}