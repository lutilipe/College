#ifndef OPACIDADE_DECORATOR_H
#define OPACIDADE_DECORATOR_H

#include "FormaDecorator.hpp"

/**
 * \Este decorador pega uma forma e adiciona opacidade a ela.
 */
class OpacidadeDecorator: public FormaDecorator {

  public:
    /**
     * \O construtor, que envia o objeto que será decorado, ou seja, a forma,
     * para o decorador de base.
     * \param o objeto que deve ser decorado.
     */
    OpacidadeDecorator(AbstractForma* formaObj, double opacidade): FormaDecorator(formaObj), _opacidade(opacidade){}
    

    /**
     * \O destruidor é o destruidor padrão produzido pelo compilador.
     */
    ~OpacidadeDecorator() {};

    /**
     * \Este método decorado adiciona uma opacidade (atributo da classe) à forma.
     * Esse atributo opacidade aparece como uma nova linha no seguinte formato:
     *  " - opacidade: ?"  
     * Onde a interrogação é a opacidade passada como parâmetro (em um intervalo de 0 a 1)
     * Para valores de 0 a 0.33 (inclusive) a opacidade é baixa
     * Para valores de 0.33 a 0.66 (inclusive) a opacidade é média
     * Para valores de 0.66 a 1 (inclusive) a opacidade é alta
     * Valores fora desse intervalo não são classificados como opacidade (não devem alterar o desenha())
     */
    std::string desenha() override;
    
    void setOpacidade(double opacidade);
    double getOpacidade();
    
  private:
    double _opacidade;
    
};

#endif