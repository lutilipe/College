//---------------------------------------------------------------------
// Arquivo	: vet.h
// Conteudo	: definicoes do TAD VETOR 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2022-04-01 - arquivo criado
// 		: 2022-04-12 - vetor dinamico 
//---------------------------------------------------------------------

#ifndef VETH
#define VETH

#include "memlog.h"

typedef struct vetor{
	double * v;
	int tam;
	int id;
} vetor_tipo;

void criaVetor(vetor_tipo * vet, int tam, int id);
void inicializaVetorNulo(vetor_tipo * vet);
void inicializaVetorAleatorio(vetor_tipo * vet);
double acessaVetor(vetor_tipo * vet);
void imprimeVetor(vetor_tipo * vet);
void escreveElemento(vetor_tipo * vet, int pos, double v);
double leElemento (vetor_tipo * vet, int pos);
void copiaVetor(vetor_tipo * src, vetor_tipo * dst, int dst_id);
void somaVetores(vetor_tipo * a, vetor_tipo * b, vetor_tipo * c);
double produtoInternoVetores(vetor_tipo * a, vetor_tipo *b);
double normaVetor(vetor_tipo *a);
void destroiVetor(vetor_tipo *a);

#endif
