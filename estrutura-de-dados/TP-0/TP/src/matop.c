#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h" 
#include "msgassert.h" 

// Define enum das operacoes do programa
enum Operations { 
    SUM = 1,
    MULTIPLY = 2,
    TRANSPOSE = 3
};

// variaveis globais para opcoes
static int opescolhida;
char logFilename[100],
    firstInMatrixFilename[100],
    secondInMatrixFilename[100],
    outMatrixFilename[100];
int regMem;

void uso() {
    // Descricao: imprime as opcoes de uso
    // Entrada: nao tem
    // Saida: impressao das opcoes de linha de comando

    fprintf(stderr,"matop\n");
    fprintf(stderr,"\t-h \t(comandos disponiveis) \n");
    fprintf(stderr,"\t-s \t(somar matrizes) \n");
    fprintf(stderr,"\t-m \t(multiplicar matrizes) \n");
    fprintf(stderr,"\t-t \t(transpor matriz)\n");
    fprintf(stderr,"\t-l \t(registrar acessos a memoria)\n");
    fprintf(stderr,"\t-p <arq>\t(arquivo de registro de acesso)\n");
    fprintf(stderr,"\t-1 <arq>\t(arquivo contendo primeira matriz)\n");
    fprintf(stderr,"\t-2 <arq>\t(arquivo contendo segunda matriz)\n");
    fprintf(stderr,"\t-o <arq>\t(arquivo de saida das operacoes de matrizes)\n");
}


void parse_args(int argc,char ** argv) {
    // Descricao: le as opcoes da linha de comando e inicializa variaveis
    // Entrada: argc e argv
    // Saida: optescolhida, regMem, logFilename, firstInMatrixFilename
    // secondInMatrixFilename, outMatrixFilename

    // variaveis externas do getopt
    extern char * optarg;
    extern int optind;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    opescolhida = -1;
    regMem = 0;
    logFilename[0] = 0;
    firstInMatrixFilename[0] = 0;
    secondInMatrixFilename[0] = 0;
    outMatrixFilename[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "mstp:1:2:lho:")) != EOF) {
        switch(c) {
            case 'm':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = MULTIPLY;
                break;
            case 's':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = SUM;
                break;
            case 't':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = TRANSPOSE;
                break;
            case 'p':
                strcpy(logFilename,optarg);
                break;
            case '1':
                strcpy(firstInMatrixFilename,optarg);
                break;
            case '2':
                strcpy(secondInMatrixFilename,optarg);
                break;
            case 'o':
                strcpy(outMatrixFilename,optarg);
                break;
            case 'l':
                regMem = 1;
                break;
            case 'h':
                uso();
                exit(1);
            default:
                uso();
                exit(1);
        }
    }
    // verificacao da consistencia das opcoes
    erroAssert(opescolhida>0,"matop - necessario escolher operacao");
    erroAssert(strlen(logFilename)>0,
        "matop - nome de arquivo de registro de acesso tem que ser definido");
    erroAssert(strlen(firstInMatrixFilename)>0,
        "matop - nome do arquivo contendo primeira matriz tem que ser definido");
    erroAssert(opescolhida == TRANSPOSE || strlen(secondInMatrixFilename)>0,
        "matop - nome do arquivo contendo segunda matriz tem que ser definido");
    erroAssert(strlen(outMatrixFilename)>0,
        "matop - nome do arquivo contendo segunda matriz tem que ser definido");
}


int main(int argc, char ** argv) {
    // Descricao: programa principal para execucao de operacoes de matrizes 
    // Entrada: argc e argv
    // Saida: depende da operacao escolhida

    // ate 3 matrizes sao utilizadas, dependendo da operacao
    Matrix a, b, c;
    // avaliar linha de comando
    parse_args(argc,argv);

    // iniciar registro de acesso
    iniciaMemLog(logFilename);

    // ativar ou nao o registro de acesso
    if (regMem) { 
        ativaMemLog();
    }
    else {
        desativaMemLog();
    }

    // execucao dependente da operacao escolhida
    switch (opescolhida) {
        case SUM:
            // cria matrizes a e b aleatorias, que sao somadas para a matriz c
            // matriz c é impressa e todas as matrizes sao destruidas
            defineFaseMemLog(0);
                initMatrixFromFile(firstInMatrixFilename, &a, 0);
                initMatrixFromFile(secondInMatrixFilename, &b, 1);
                createMatrix(&c, a.M, a.N, 2);
                initNullMatrix(&c);
            defineFaseMemLog(1);
                accessMatrix(&a);
                accessMatrix(&b);
                accessMatrix(&c);
                sumMatrix(&a, &b, &c);
                writeMatrixToFile(outMatrixFilename, &c);
            defineFaseMemLog(2);
                accessMatrix(&c);
                if (regMem) printMatrix(&c);
                destroyMatrix(&a);
                destroyMatrix(&b);
                destroyMatrix(&c);
            break;
        case MULTIPLY:
            // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
            // matriz c é impressa e todas as matrizes sao destruidas
            defineFaseMemLog(0);
                initMatrixFromFile(firstInMatrixFilename, &a, 0);
                initMatrixFromFile(secondInMatrixFilename, &b, 1);
                createMatrix(&c, a.M, b.N, 2);
                initNullMatrix(&c);
            defineFaseMemLog(1);
                accessMatrix(&a);
                accessMatrix(&b);
                accessMatrix(&c);
                multiplyMatrix(&a, &b, &c);
                writeMatrixToFile(outMatrixFilename, &c);
            defineFaseMemLog(2);
                accessMatrix(&c);
                if (regMem) printMatrix(&c);
                destroyMatrix(&a);
                destroyMatrix(&b);
                destroyMatrix(&c);
        break;
        case TRANSPOSE:
            // cria matriz a aleatoria A, que e transposta e armazenada em B, impressa e destruida
            defineFaseMemLog(0);
                initMatrixFromFile(firstInMatrixFilename, &a, 0);
                createMatrix(&b, a.N, a.M, 1);
                initNullMatrix(&b);
            defineFaseMemLog(1);
                accessMatrix(&a);
                accessMatrix(&b);
                transposeMatrix(&a, &b);
                writeMatrixToFile(outMatrixFilename, &b);
            defineFaseMemLog(2);
                accessMatrix(&b);
                if (regMem) printMatrix(&b);
                destroyMatrix(&a);
                destroyMatrix(&b);
        break;
    default:
        // nao deve ser executado, pois ha um erroAssert em parse_args
        uso();
        exit(1);
    }

    // conclui registro de acesso
    return finalizaMemLog();
}

