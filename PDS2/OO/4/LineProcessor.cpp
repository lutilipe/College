#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"

void LinePrinter::processaLinha(const std::string &str) {
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana/100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais <<
    std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const {
  std::regex regularExp("(\\s*\\d+\\s*)+");
  return std::regex_match(str, regularExp);
}

void ContadorNumNaturais::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  unsigned number, total = 0;
  std::string tmp;
  ss << str;
  while (!ss.eof()) {
    ss >> tmp;
    if (std::stringstream(tmp) >> number) {
      total += number;
    }
  }
  std::cout << total << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const {
  std::regex regularExp("(\\s*[A-Za-z]+\\s+\\d+\\s?)+");
  return std::regex_match(str, regularExp);
}

void LeitorDeFutebol::processaLinha(const std::string &str) {
  std::stringstream ss;
  std::string time1, time2;
  unsigned res1, res2;
  ss << str;
  while (!ss.eof()) {
    ss >> time1 >> res1 >> time2 >> res2;
  }
  if (res1 > res2) {
      std::cout << "Vencedor: " << time1 << std::endl;
  } else if (res2 > res1) {
      std::cout << "Vencedor: " << time2 << std::endl;
  } else {
      std::cout << "Empate" << std::endl;
  }
}

void ContadorDePalavras::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string word;

  unsigned count = 0;
  while (!ss.eof()) {
    if (ss >> word) {
      count++;
    }
  }
  std::cout << count << std::endl;
}

bool InversorDeFrases::linhaValida(const std::string &str) const {
  std::regex regularExp("[0-9!@#$%^&*()_+\\-=\\[\\]{};':\\|,.<>\\/?]");
  return !std::regex_search(str, regularExp);
}

void InversorDeFrases::processaLinha(const std::string &str) {
    std::stringstream stream(str);
    std::vector<std::string> words;
    for ( std::string word; stream >> word; ) {
        words.push_back(word);
    }
    for (int i = words.size() - 1; i >= 0; i--) {
        if (i == 0) {
            std::cout << words[i];
        } else {
            std::cout << words[i] << " ";
        }
    }
    std::cout << std::endl;
}

bool EscritorDeDatas::linhaValida(const std::string &str) const {
  std::regex regularExp("\\s*\\d\\d?/\\d\\d?/\\d{4}");
  return std::regex_match(str, regularExp);
}

void EscritorDeDatas::processaLinha(const std::string &str) {
    std::stringstream ss(str);
    std::string allMounth[12] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez" };
    std::string d, mm, y;
    getline(ss, d, '/');
    getline(ss, mm, '/');
    getline(ss, y, '/');
    std::cout << allMounth[std::stoi(mm)-1] << std::endl;
}