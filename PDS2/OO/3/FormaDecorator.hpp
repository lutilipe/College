#ifndef FORMA_DECORATOR_H
#define FORMA_DECORATOR_H

#include "AbstractForma.hpp"

/**
 * \Este é o decorador básico. Todos os outros decoradores terão que implementá-lo.
 */
class FormaDecorator: public AbstractForma {

public:
  /**
   * \O construtor, que simplesmente liga a forma abstrato ao estado interno
   * deste objeto.
   * \param o objeto que deve ser decorado.
   */
  FormaDecorator(AbstractForma* formaObj): _formaObj(formaObj) {}

  /**
   * \O destruidor é o destruidor padrão produzido pelo compilador.
   */
  ~FormaDecorator() {};

  /**
   * \Este é o método que terá que ser sobrescrito por qualquer decorador que
   * rodeia esta classe.
   * \retornar o desenho (a string) decorada não modificada.
   */
  std::string desenha() override {
    return _formaObj->desenha();
  }

  private:
  AbstractForma *_formaObj; ///< Um ponteiro para o objeto decorado.
};

#endif