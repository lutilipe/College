#include "Biblioteca.hpp"
#include "LivroNaoFiccao.hpp"
#include "LivroInfantil.hpp"
#include "LivroFiccao.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    Biblioteca biblioteca;
    string iniciar_busca;
    string titulo,  autor, subgenero, assunto;
    int anoPublicacao, faixaetm;
    vector<Livro*> livros;
  
    while(cin >> iniciar_busca){
    //cout <<"digite algo" << endl;
    
    if(iniciar_busca == "quit"){
      break;
    }
    else if (iniciar_busca == "add_f") {
      cin >> titulo >> autor >> anoPublicacao >> subgenero;
      LivroFiccao *ficcao = new LivroFiccao(titulo, autor, anoPublicacao, subgenero);
      biblioteca.add_livro(ficcao);
      livros.push_back(ficcao);
  }
      
    else if (iniciar_busca == "add_nf") {
        cin >> titulo >> autor >> anoPublicacao >> assunto ;
        LivroNaoFiccao *nficcao = new LivroNaoFiccao(titulo, autor, anoPublicacao, assunto);
        biblioteca.add_livro(nficcao);
        livros.push_back(nficcao);
    }
      
      else if(iniciar_busca == "add_i"){
        cin >> titulo >> autor >> anoPublicacao >> faixaetm;
        LivroInfantil *infantil = new LivroInfantil(titulo, autor, anoPublicacao, faixaetm);
        biblioteca.add_livro(infantil);
        livros.push_back(infantil);

      }
        else if (iniciar_busca == "rm") {
          int id;
          cin >> id;
          biblioteca.remove_livro(id);
          continue;
        }

          else if(iniciar_busca == "find"){
            int id;
            cin >> id;
            biblioteca.find_livro(id);
          }
      else if(iniciar_busca == "list"){
          biblioteca.list_livros();
      }
    }
  
  return 0;
}