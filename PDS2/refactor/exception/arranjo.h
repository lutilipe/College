#pragma once

#include <cassert>
#include <vector>

// Define um arranjo de qualquer Tipo cujos índices variam em
// qualquer intervalo, inclusive negativos.
template <class Tipo> 
class Arranjo {
  public:
    // Cria um arranjo cujos índices variam de 'inicio' até 'fim'.
    // PRECONDIÇÃO: fim >= inicio.
    Arranjo(int inicio, int fim);

    // Altera o valor do índice i.
    // PRECONDIÇÃO: i está dentro do intervalo de índices do vetor.
    void atribuir(int i, Tipo valor);

    // Retorna o valor do índice i.
    // PRECONDIÇÕES: 
    // (1) i está dentro do intervalo de índices do vetor.
    // (2) i foi inicializando anteriormente.
    Tipo valor(int i) const; 
  
  private:
    int inicio_;  // Primeiro índice válido do arranjo.
    int fim_;  // Último índice válido do arranjo.
    std::vector<Tipo> elementos_;  // Elementos do arranjo.
    std::vector<int> indices_;
};

// DEFINIÇÃO DAS CLASSES DE EXCEÇÃO.

struct ExcecaoIntervaloVazio {
    int inicio;
    int fim;
};

struct ExcecaoIndiceInvalido {
    int indice;
    int inicio;
    int fim;
};

struct ExcecaoIndiceNaoInicializado {
    int indice;
};

// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE.

template <class Tipo> 
Arranjo<Tipo>::Arranjo(int inicio, int fim) {
    if (inicio > fim) {
        throw ExcecaoIntervaloVazio{inicio, fim};
    }
    inicio_ = inicio;
    fim_ = fim; 
    elementos_.resize(fim - inicio + 1);
}

template <class Tipo> 
void Arranjo<Tipo>::atribuir(int i, Tipo valor) {
  int j = i - inicio_;
  if (!(j >= 0 && j < elementos_.size()))
    throw ExcecaoIndiceInvalido{indice: i, inicio: inicio_, fim: fim_};
  elementos_[j] = valor;
  indices_.push_back(i);
}

bool includes(std::vector<int> v, int i) {
    bool includes = false;
    for (auto const& ind : v) {
        if (ind == i) {
            includes = true;
        }
    }
    return includes;
}

template <class Tipo> 
Tipo Arranjo<Tipo>::valor(int i) const { 
  int j = i - inicio_;     
  if (!(j >= 0 && j < elementos_.size()))
    throw ExcecaoIndiceInvalido{indice: i, inicio: inicio_, fim: fim_};
  if (!includes(indices_, i))
    throw ExcecaoIndiceNaoInicializado{indice: i};
  return elementos_[j];
}