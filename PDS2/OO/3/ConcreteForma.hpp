#ifndef CONCRETE_FORMA_H
#define CONCRETE_FORMA_H

#include "AbstractForma.hpp"

/**
 * \Este é o componente concreto do decorador. Ele fornece uma implementação
 * muito simples para o fluxo abstrato.
 */
class ConcreteForma: public AbstractForma {

public:
  /**
   * \Construtor. Ele recebe uma string e a liga à string interna que essa classe
   * encapsula
   * \param forma: a string que será representada por este objeto.
   */
  ConcreteForma(const std::string forma): _forma(forma) {}

  /**
   * \simplesmente retorna o "desenho" do objeto, aqui representado pela string interna. Sem modificações.
   * \retornar o "desenho" (a string) não modificada encapsulada por este objeto.
   */
  std::string desenha() override { return this->_forma; }

  private:
    std::string _forma; ///< A string encapsulada por este objeto.
};

#endif