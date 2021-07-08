#ifndef TAMANHO_DECORATOR_H
#define TAMANHO_DECORATOR_H

#include "FormaDecorator.hpp"

/**
 * \Este decorador pega uma forma e adiciona cor a a ela.
 */
class TamanhoDecorator: public FormaDecorator {

public:
  /**
   * \O construtor, que envia o objeto que será decorado, ou seja, a forma,
   * para o decorador de base.
   * e seta _tamanho do objeto
   * \param o objeto que deve ser decorado.
   */
  TamanhoDecorator(AbstractForma* formaObj, int tamanho): FormaDecorator(formaObj), _tamanho(tamanho) {}
  

  /**
   * \O destruidor é o destruidor padrão produzido pelo compilador.
   */
  ~TamanhoDecorator() {};

  /**
   * \Este método decorado adiciona um tamanho (atributo da classe) à forma.
   *    * Esse atributo tamanho aparece como uma nova linha no seguinte formato:
   *  " - tamanho: ?"  
   * Onde a interrogação é o tamanho passada como parâmetro
   */
  std::string desenha() override;
  
  void setTamanho(int tamanho);
  int getTamanho();
  
private:
    int _tamanho;
};

#endif