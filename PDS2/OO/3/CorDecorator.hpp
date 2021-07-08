#ifndef COR_DECORATOR_H
#define COR_DECORATOR_H

#include "FormaDecorator.hpp"

/**
 * \Este decorador pega uma forma e adiciona cor a a ela.
 */
class CorDecorator: public FormaDecorator {

public:
  /**
   * \O construtor, que envia o objeto que será decorado, ou seja, a forma,
   * para o decorador de base.
   * e seta _cor do objeto
   * \param o objeto que deve ser decorado.
   */
  CorDecorator(AbstractForma* formaObj, std::string cor): FormaDecorator(formaObj), _cor(cor) {}
  

  /**
   * \O destruidor é o destruidor padrão produzido pelo compilador.
   */
  ~CorDecorator() {};

  /**
   * \Este método decorado adiciona uma cor (atributo da classe) à forma.
   * Esse atributo cor aparece como uma nova linha no seguinte formato:
   *  " - cor: ?"  
   * Onde a interrogação é a cor passada como parâmetro
   */
  std::string desenha() override;
  
  void setCor(std::string cor);
  std::string getCor();
  
private:
    std::string _cor;
};

#endif