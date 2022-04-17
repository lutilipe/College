//---------------------------------------------------------------------
// Arquivo      : vetop.c
// Conteudo     : programa de avaliacao do TAD VET 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2022-04-01 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "vet.h"
#include "memlog.h" 
#include "msgassert.h" 

// definicoes de operacoes a serem testadas
#define OPSOMA 1
#define OPPRODUTOINTERNO 2
#define OPNORMA 3

typedef struct opt{
  int opescolhida;
  char lognome[100];
  int tam, regmem;
} opt_tipo;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"vetop\n");
  fprintf(stderr,"\t-d <int>\t(dimensao)\n");
  fprintf(stderr,"\t-s \t\t(somar vetores) \n");
  fprintf(stderr,"\t-i \t\t(produto interno de dois vetores) \n");
  fprintf(stderr,"\t-n \t\t(norma vetor)\n");
  fprintf(stderr,"\t-p <arq>\t(arquivo de registro de acesso)\n");
  fprintf(stderr,"\t-l \t\t(registrar acessos a memoria)\n");
}


void parse_args(int argc,char ** argv, opt_tipo * opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc, argv, opt
// Saida: opt
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opt->opescolhida = -1;
     opt->tam = -1;
     opt->regmem = 0;
     opt->lognome[0] = 0;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "isnp:d:lh")) != EOF)
       switch(c) {
         case 'i':
		  avisoAssert(opt->opescolhida==-1,
		              "Mais de uma operacao escolhida");
	          opt->opescolhida = OPPRODUTOINTERNO;
                  break;
         case 's':
		  avisoAssert(opt->opescolhida==-1,
		              "Mais de uma operacao escolhida");
	          opt->opescolhida = OPSOMA;
                  break;
         case 'n':
		  avisoAssert(opt->opescolhida==-1,
		              "Mais de uma operacao escolhida");
	          opt->opescolhida = OPNORMA;
                  break;
         case 'p': 
	          strcpy(opt->lognome,optarg);
		  break;
         case 'd': 
	          opt->tam = atoi(optarg);
		  break;
         case 'l': 
	          opt->regmem = 1;
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
       // verificacao da consistencia das opcoes
       erroAssert(opt->opescolhida>0,"vetop - necessario escolher operacao");
       erroAssert(strlen(opt->lognome)>0,
         "vetop - nome de arquivo de registro de acesso tem que ser definido");
       erroAssert(opt->tam>0, "matop - tamanho do vetor tem que ser positivo");
}


int main(int argc, char ** argv)
// Descricao: programa principal para execucao de operacoes de matrizes 
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  vetor_tipo a, b, c;
  double norma, prodinterno;
  opt_tipo opt;
  // avaliar linha de comando
  parse_args(argc,argv,&opt);

  // iniciar registro de acesso
  iniciaMemLog(opt.lognome);

  // ativar ou nao o registro de acesso
  if (opt.regmem){ 
    ativaMemLog();
  }
  else{
    desativaMemLog();
  }

  // execucao dependente da operacao escolhida
  switch (opt.opescolhida){
    case OPSOMA:
         // cria vetores a e b aleatorios, que sao somados para o vetor c
	 // vetor c é impresso e todos os vetores sao destruidos
	 defineFaseMemLog(0);
         criaVetor(&a,opt.tam,0);
         inicializaVetorAleatorio(&a);
         criaVetor(&b,opt.tam,1);
         inicializaVetorAleatorio(&b);
         criaVetor(&c,opt.tam,2);
         inicializaVetorNulo(&c);
	 defineFaseMemLog(1);
         acessaVetor(&a);
         acessaVetor(&b);
         acessaVetor(&c);
         somaVetores(&a,&b,&c);
	 defineFaseMemLog(2);
         acessaVetor(&c);
	 if (opt.regmem) imprimeVetor(&c);
         destroiVetor(&a);
         destroiVetor(&b);
         destroiVetor(&c);
	 break;
    case OPPRODUTOINTERNO:
         // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
	 // matriz c é impressa e todas as matrizes sao destruidas
	 defineFaseMemLog(0);
         criaVetor(&a,opt.tam,0);
         inicializaVetorAleatorio(&a);
         criaVetor(&b,opt.tam,1);
         inicializaVetorAleatorio(&b);
         criaVetor(&c,opt.tam,2);
         inicializaVetorNulo(&c);
	 defineFaseMemLog(1);
         acessaVetor(&a);
         acessaVetor(&b);
         acessaVetor(&c);
         prodinterno = produtoInternoVetores(&a,&b);
	 if (opt.regmem) printf("Produto interno %f\n",prodinterno);
	 defineFaseMemLog(2);
         destroiVetor(&a);
         destroiVetor(&b);
         destroiVetor(&c);
	 break;
    case OPNORMA:
         // cria matriz a aleatoria, que e transposta, impressa e destruida
	 defineFaseMemLog(0);
         criaVetor(&a,opt.tam,0);
         inicializaVetorAleatorio(&a);
	 defineFaseMemLog(1);
         acessaVetor(&a);
	 norma = normaVetor(&a);
	 if (opt.regmem) printf("Norma %f\n",norma);
	 defineFaseMemLog(2);
         destroiVetor(&a);
	 break;
   default:
         // nao deve ser executado, pois ha um erroAssert em parse_args
         uso();
	 exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}

