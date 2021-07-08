#include <iostream>

#include "ConcreteForma.hpp"
#include "CorDecorator.hpp"
#include "TamanhoDecorator.hpp"
#include "OpacidadeDecorator.hpp"

AbstractForma* criaFormaCompleta(std::string forma, std::string cor, int tamanho, double opacidade) {
  AbstractForma* abs = new ConcreteForma(forma);
  abs = new TamanhoDecorator(abs, tamanho);
  abs = new CorDecorator(abs, cor);
  return new OpacidadeDecorator(abs, opacidade);
}

AbstractForma* adicionarTamanho(std::string forma, int tamanho) {
  AbstractForma* abs = new ConcreteForma(forma);
  return new TamanhoDecorator(abs, tamanho);
}

AbstractForma* adicionarCor(std::string forma, std::string cor) {
  AbstractForma* abs = new ConcreteForma(forma);
  return new CorDecorator(abs, cor);
}

AbstractForma* adicionarOpacidade(std::string forma, double opacidade) {
  AbstractForma* abs = new ConcreteForma(forma);
  return new OpacidadeDecorator(abs, opacidade);
}

bool is_int(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_double(const std::string& s)
{
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}

int main() {
  std::string forma;
  std::getline(std::cin, forma);
  std::cout << adicionarCor(forma, "azul")->desenha() << std::endl;
  std::cout << adicionarTamanho(forma, 12)->desenha() << std::endl;
  std::cout << adicionarOpacidade(forma, 0.66)->desenha() << std::endl;
  std::cout << criaFormaCompleta(forma, "verde", 13, 2.1)->desenha() << std::endl;
  
  std::getline(std::cin, forma);
  AbstractForma* abs = new ConcreteForma(forma);
  std::string opcao;
  while(std::cin >> opcao){
        if(is_int(opcao)){
            abs = new TamanhoDecorator(abs, std::stoi(opcao));
        }
        else if(is_double(opcao)){
            abs = new OpacidadeDecorator(abs, std::stod(opcao));
        }
        else{
            abs = new CorDecorator(abs, opcao);
        }
  }
  std::cout << abs->desenha() << std::endl;
  
}