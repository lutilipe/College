#include <iostream>
#include <cstdlib> // system()
using namespace std;
#include "List.h"

void clearscreen() {
if (system( "clear" )) system( "cls" );
}

int main(int argc, char *argv[])
{
    try {
        // Cria Lista
        List<int> A;
        cout << "Criacao da Lista A:" << endl;
        cout << "-> Lista A: " << A << endl;
        
        //Insere elementos no Final da lista
        A.push_back(3);
        A.push_back(4);
        A.push_back(5);
        A.push_back(6);
        A.push_back(6);
        A.push_back(1);
        A.push_back(2);
        cout << "A.push_back(3), A.push_back(4), A.push_back(5), A.push_back(6), A.push_back(6), A.push_back(1), A.push_back(2)" << endl;
        cout << "-> Lista A " << A << endl;
        
        //Insere elementos no Inicio da lista
        A.push_front(8);
        A.push_front(9);
        A.push_front(4);
        A.push_front(9);
        cout << "A.push_front(8), A.push_front(9), A.push_front(4), A.push_front(9)" << endl;
        cout << "-> Lista A " << A << endl;
        
        // remove os elementos de valor igual a 6 existentes na lista 
        A.erase(6);
        cout << "A.erase(6)" << endl;
        cout << "-> Lista A " << A << endl;
        
        // retorna o tamanho da lista
        int tam;
        tam = A.size();
        cout << "tam = A.size" << endl;
        cout << "-> tamanho da Lista A = " << tam << endl << endl;
    } catch (EmptyListException &e) {
        cout << e.what() << endl;
    } catch (InvalidElementException &e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "Erro desconhecido" << endl;
    }
     
    cout << "\nPressione qualquer tecla para continuar...";
    getchar();
    clearscreen();
}
