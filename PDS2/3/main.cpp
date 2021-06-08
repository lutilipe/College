#include <iostream>
#include <iomanip>

#include "Triangulo.hpp"
#include "Ponto2D.hpp"

using namespace std;

int main() {
  
  Ponto2D pontos[3]; 
  double x, y;

  // Triangulo 1
  for (int i=0; i<3; i++) {
    cin >> x >> y;
    pontos[i] = Ponto2D(x, y);
  }
  Triangulo* triangulo1 = new Triangulo(pontos[0], pontos[1], pontos[2]);

  // Triangulo 2
  for (int i=0; i<3; i++) {
    cin >> x >> y;
    pontos[i] = Ponto2D(x, y);
  }
  Triangulo* triangulo2 = new Triangulo(pontos[0], pontos[1], pontos[2]);
  
  cout << fixed << showpoint; 
  cout << setprecision(2);
  
  // Imprimindo as informacoes
  cout << triangulo1->calcular_area() << " " << triangulo2->calcular_area() << endl;
  cout << triangulo1->calcular_perimetro() << " " << triangulo2->calcular_perimetro() << endl;
  cout << triangulo1->comparar_area(triangulo2) << " " << triangulo2->comparar_area(triangulo1) << endl;

  delete triangulo1;
  delete triangulo2;

  return 0;
}