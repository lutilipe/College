#include "TamanhoDecorator.hpp"

std::string TamanhoDecorator::desenha() {
    return FormaDecorator::desenha() + "\n- cor: " + std::to_string(this->_tamanho);
}

void TamanhoDecorator::setTamanho(int tamanho) {
    this->_tamanho = tamanho;
}

int TamanhoDecorator::getTamanho() {
    return this->_tamanho;
}
