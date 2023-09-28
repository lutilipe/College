#include "Retangulo.hpp"
#include "Figura.hpp"
#include "Circulo.hpp"
#include "Ponto.hpp"

void t1() {
  Figura* A = new Retangulo(1, 1, 3, 3);
  cout << "Contem: " << A->contem(Ponto(4,2)) << endl;
  cout << "Contem: " << A->contem(Ponto(5,2)) << endl;
  delete A;
}

void t2() {
  Figura* A = new Circulo(1, 1, 3);
  cout << "Contem: " << A->contem(Ponto(2,2)) << endl;
  cout << "Contem: " << A->contem(Ponto(4,1)) << endl;
  cout << "Contem: " << A->contem(Ponto(-1,-1)) << endl;
  cout << "Contem: " << A->contem(Ponto(5,2)) << endl;
  delete A;
}

void t3() {
  Figura* A = new Retangulo(1, 1, 3, 3);
  Figura* B = new Circulo(4.5, 2.5, 1.5);
  Figura* C = *A + *B;
  cout << "Contem: " << C->contem(Ponto(2, 2)) << endl;
  cout << "Contem: " << C->contem(Ponto(2, 0)) << endl;
  delete C;
  delete A;
  delete B;
}

void t4() {
  Figura* A = new Retangulo(1, 1, 3, 3);
  Figura* B = new Circulo(4.5, 2.5, 1.5);
  Figura* C = *A - *B;
  cout << "Contem: " << C->contem(Ponto(2, 3)) << endl;
  cout << "Contem: " << C->contem(Ponto(4, 2)) << endl;
  delete C;
  delete A;
  delete B;
}

void t5() {
  Figura* A = new Retangulo(1, 2, 5, 5);
  Figura* B = new Retangulo(2, 3, 3, 3);
  Figura* C = new Circulo(3.5, 4.5, 3.5);
  Figura* D = new Circulo(3.5, 4.5, 1.0);
  Figura* E = *A - *B;
  Figura* F = *C - *E;
  Figura* G = *F - *D;
  cout << "Contem: " << G->contem(Ponto(0.5, 4)) << endl;
  cout << "Contem: " << G->contem(Ponto(1.5, 6.5)) << endl;
  cout << "Contem: " << G->contem(Ponto(3.0, 5.0)) << endl;
  cout << "Contem: " << G->contem(Ponto(3.5, 1.5)) << endl;
  delete A;
  delete B;
  delete C;
  delete D;
  delete E;
  delete F;
  delete G;
}

void t6() {
  Figura* A = new Retangulo(0, 3, 8, 2);
  Figura* B = new Retangulo(3, 0, 2, 8);
  Figura* C = new Circulo(4, 4, 1);
  Figura* D = *A + *B;
  Figura* E = *D - *C;
  cout << "Contem: " << D->contem(Ponto(4.0, 4.0)) << endl;
  cout << "Contem: " << E->contem(Ponto(4.0, 4.0)) << endl;
  cout << "Contem: " << E->contem(Ponto(1.0, 4.0)) << endl;
  cout << "Contem: " << E->contem(Ponto(4.0, 7.0)) << endl;
  cout << "Contem: " << E->contem(Ponto(6.0, 1.0)) << endl;
  delete A;
  delete B;
  delete C;
  delete D;
  delete E;
}

void t7() {
  Figura* A = new Retangulo(1, 1, 3, 3);
  Figura* B = new Circulo(4.5, 2.5, 1.5);
  Figura* C = *A + *B;
  Figura* D = *A - *B;
  cout << "Contem: " << D->contem(Ponto(4.0, 2.0)) << endl;
  cout << "Contem: " << D->contem(Ponto(2.0, 3.0)) << endl;
  Figura* E = new Circulo(3.5, 2.5, 1.5);
  Figura* F = new Retangulo(3, 0, 3, 3);
  Figura* G = *F - *E;
  cout << "Contem: " << G->contem(Ponto(4.0, 2.0)) << endl;
  cout << "Contem: " << G->contem(Ponto(5.0, 1.0)) << endl;
  Figura* H = *D + *G;
  cout << "Contem: " << H->contem(Ponto(4.0, 2.0)) << endl;
  cout << "Contem: " << H->contem(Ponto(5.0, 1.0)) << endl;
  cout << "Contem: " << H->contem(Ponto(2.0, 3.0)) << endl;
  delete A;
  delete B;
  delete C;
  delete D;
  delete E;
  delete F;
  delete G;
  delete H;
}

int main() {
  int testType = 0;
  std::cin >> testType;
  switch (testType) {
    case 1:
      t1();
      break;
    case 2:
      t2();
      break;
    case 3:
      t3();
      break;
    case 4:
      t4();
      break;
    case 5:
      t5();
      break;
    case 6:
      t6();
      break;
    case 7:
      t7();
      break;
    default:
      break;
  }
}