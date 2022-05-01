#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x,y) (x+=y,y=x-y,x-=y)

void createMatrix(Matrix * mat, int tx, int ty, int id)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat
{
  // verifica se os valores de tx e ty são validos
  erroAssert(tx>0,"Dimensao nula");
  erroAssert(ty>0,"Dimensao nula");
  erroAssert(tx<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(ty<=MAXTAM,"Dimensao maior que permitido");

  // inicializa as dimensoes da matriz
  mat->i = tx;
  mat->j = ty;
  // inicializa o identificador da matriz, para rastreamento
  mat->id = id;
}

void initNullMatrix(Matrix * mat)
// Descricao: inicializa mat com valores nulos 
// Entrada: mat
// Saida: mat
{
  int i, j;
  // inicializa todos os elementos da matriz com 0, por seguranca 
  for (i=0; i<MAXTAM; i++){
    for(j=0; j<MAXTAM; j++){
      mat->m[i][j] = 0;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
}

void initRandomMatrix(Matrix * mat)
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat 
// Saida: mat
{
  int i, j;
  // inicializa a matriz com valores nulos, por seguranca
  initNullMatrix(mat);
  // inicializa a parte alocada da matriz com valores aleatorios
  for (i=0; i<mat->i; i++){
    for(j=0; j<mat->j; j++){
      mat->m[i][j] = drand48()*INITRANDOMRANGE;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
}

double accessMatrix(Matrix * mat)
// Descricao: acessa mat para fins de registro de acesso 
// Entrada: mat 
// Saida: mat
{
  int i, j;
  double aux, s=0.0;
  for (i=0; i<mat->i; i++){
    for(j=0; j<mat->j; j++){
      aux = mat->m[i][j];
      s+=aux;
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
  return s; // apenas para evitar que acesso seja eliminado
}

void printMatrix(Matrix * mat)
// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: mat
// Saida: impressao na saida padrao (stdout) 
{
  int i,j;

  // seguranca, mas erro não deve acontecer jamais
  erroAssert(mat->i<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(mat->j<=MAXTAM,"Dimensao maior que permitido");

  // imprime os identificadores de coluna
  printf("%9s"," ");
  for(j=0; j<mat->j; j++)
    printf("%8d ",j);
  printf("\n");

  // imprime as linhas
  for (i=0; i<mat->i; i++){
    printf("%8d ",i);
    for(j=0; j<mat->j; j++){
      printf("%8.2f ",mat->m[i][j]);
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
    printf("\n");
  }
}

void writeElement(Matrix * mat, int x, int y, double v)
// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
{
  // verifica se x e y sao validos
  erroAssert((x<0)||(x>=mat->i),"Indice invalido");
  erroAssert((y<0)||(y>=mat->j),"Indice invalido");

  mat->m[x][y] = v;
  ESCREVEMEMLOG((long int)(&(mat->m[x][y])),sizeof(double),mat->id);
}

double readElement (Matrix * mat, int x, int y)
// Descricao: retorna o elemento (x,y) de mat 
// Entrada: mat, x, y
// Saida: mat[x][y] 
{
  // verifica se x e y sao validos
  erroAssert((x<0)||(x>=mat->i),"Indice invalido");
  erroAssert((y<0)||(y>=mat->j),"Indice invalido");

  LEMEMLOG((long int)(&(mat->m[x][y])),sizeof(double),mat->id);
  return mat->m[x][y];
}

void copyMatrix(Matrix *src, Matrix * dst, int dst_id)
// Descricao: faz uma copia de src em dst
// Entrada: src, dst_id
// Saida: dst
{
  int i,j;

  // cria novamente a matriz dst para ajustar as suas dimensoes
  createMatrix(dst,src->i, src->j,dst_id);
  // inicializa a matriz dst como nula
  initNullMatrix(dst);
  // copia os elementos da matriz src
  for (i=0; i<src->i; i++){
    for(j=0; j<src->j; j++){
      dst->m[i][j] = src->m[i][j];
      LEMEMLOG((long int)(&(src->m[i][j])),sizeof(double),src->id);
      ESCREVEMEMLOG((long int)(&(dst->m[i][j])),sizeof(double),dst->id);
    }
  }
}

void sumMatrix(Matrix *a, Matrix *b, Matrix *c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  int i,j;
  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->i==b->i,"Dimensoes incompativeis");
  erroAssert(a->j==b->j,"Dimensoes incompativeis");

  // inicializa a matriz c garantindo a compatibilidade das dimensoes
  createMatrix(c,a->i, a->j, c->id);
  initNullMatrix(c);

  // faz a soma elemento a elemento
  for (i=0; i<a->i; i++){
    for(j=0; j<a->j; j++){
      c->m[i][j] = a->m[i][j]+b->m[i][j];
      LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      LEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
      ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
    }
  }
}

void multiplyMatrix(Matrix *a, Matrix *b, Matrix *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  int i,j,k;
  // verifica a compatibilidade das dimensoes 
  erroAssert(a->j==b->i,"Dimensoes incompativeis");

  // cria e inicializa a matriz c
  createMatrix(c,a->i, b->j,c->id);
  initNullMatrix(c);

  // realiza a multiplicacao de matrizes
  for (i=0; i<c->i;i++){
    for (j=0; j<c->j;j++){
      for (k=0; k<a->j;k++){
        c->m[i][j] += a->m[i][k]*b->m[k][j];
        LEMEMLOG((long int)(&(a->m[i][k])),sizeof(double),a->id);
        LEMEMLOG((long int)(&(b->m[k][j])),sizeof(double),b->id);
        ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
      }
    }
  }
}

void transposeMatrix(Matrix *a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{
  int i,j,dim;
  
  // determina a maior dimensao entre i e j
  dim = (a->i>a->j?a->i:a->j);

  // faz a transposicao como se a matriz fosse quadrada
  for (i=0; i<dim; i++){
    for(j=i+1; j<dim; j++){
      ELEMSWAP((a->m[i][j]),(a->m[j][i]));
      ESCREVEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      ESCREVEMEMLOG((long int)(&(a->m[j][i])),sizeof(double),a->id);
    }
  }
  // inverte as dimensoes da matriz transposta
  ELEMSWAP(a->i,a->j);
}

void destroyMatrix(Matrix *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  // apenas um aviso se a matriz for destruida mais de uma vez
  avisoAssert(((a->i>0)&&(a->j>0)),"Matriz já foi destruida");

  // torna as dimensoes invalidas
  a->id = a->i = a->j = -1;
}
