#include "OpacidadeDecorator.hpp"

std::string OpacidadeDecorator::desenha() {
    if (this->_opacidade >= 0 && this->_opacidade <= 0.33) {
        return FormaDecorator::desenha() + "\n- opacidade: " + "baixa";
    } else if (this->_opacidade > 0.33 && this->_opacidade <= 0.66) {
        return FormaDecorator::desenha() + "\n- opacidade: " + "média";
    } else if (this->_opacidade > 0.66 && this->_opacidade <= 1) {
        return FormaDecorator::desenha() + "\n- opacidade: " + "alta";
    } else {
        return FormaDecorator::desenha();
    }
}

double OpacidadeDecorator::getOpacidade() {
    return this->_opacidade;
}

void OpacidadeDecorator::setOpacidade(double opacidade) {
    this->_opacidade = opacidade;
}