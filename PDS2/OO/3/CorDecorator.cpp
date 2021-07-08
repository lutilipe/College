#include "CorDecorator.hpp"

std::string CorDecorator::desenha() {
  return FormaDecorator::desenha() + "\n- cor: " + this->_cor;
}

void CorDecorator::setCor(std::string cor) {
  this->_cor = cor;
}

std::string CorDecorator::getCor() {
  return this->_cor;
}
