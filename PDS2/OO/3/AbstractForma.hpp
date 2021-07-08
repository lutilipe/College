#ifndef ABSTRACT_FORMA_H
#define ABSTRACT_FORMA_H

#include <string>

/**
 * \Uma classe abstrata que denota uma forma. Em nosso caso, uma forma é apenas
 * uma string, ou seja, uma sequência de caracteres.
 */
class AbstractForma {
public:
  /**
   * Este é o método abstrato que "desenha" o objeto. Não estaremos mostrando
   * uma figura de fato (como seria o efeito em um aplicação prática).
   * No exemplo em o "desenho" éa string que esta classe codifica.
   * Observe que esse método não tem corpo, ou seja, é atribuído a zero. retorna
   * o "desenho" que esta forma representa.
   */
  virtual std::string desenha() = 0;

  /**
   * O destruidor virtual. Cada classe abstrata, por exemplo, uma classe com um
   * método virtual atribuído a zero, precisa de um destruidor virtual. Por que
   * a classe abstrata precisa de um destruidor virtual? Qualquer usuário de sua
   * classe provavelmente terá um ponteiro para a classe abstrata, não um
   * ponteiro para a implementação concreta. Portanto, quando eles tentarem
   * excluí-lo, se o destruidor não for virtual, eles chamarão o destruidor da
   * classe abstrata (ou o padrão fornecido pelo compilador, se você não
   * especificou um), não o destruidor da classe derivada. Se houver memória a
   * ser liberada na classe concreta, o destruidor da classe abstrata não será
   * capaz de fazê-lo. Isso levará a um vazamento de memória.
   */
  virtual ~AbstractForma() {};
};

#endif