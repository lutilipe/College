#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "msgassert.h"
#include "utils.h"

using namespace std;

string logFilename,
    inputFile,
    outputFile;
int regMem = 0,
    minPartSize = 0,
    medianSize = 0;

void uso() {
    fprintf(stderr,"Analyzer\n");
    fprintf(stderr,"\t-h \t(comandos disponiveis)\n");
    fprintf(stderr,"\t-l \t(registrar acessos a memoria)\n");
    fprintf(stderr,"\t-p <arq>\t(arquivo de entrada da analise de memoria)\n");
    fprintf(stderr,"\t-i|I <arq>\t(arquivo de entrada)\n");
    fprintf(stderr,"\t-o|O <arq>\t(arquivo de saida)\n");
    fprintf(stderr,"\t-m|M \t(numero da mediana)\n");
    fprintf(stderr,"\t-s|S \t(tamanho minimo da particao para usar o QuickSort)\n");
}


void parse_args(int argc,char ** argv) {
    int c;

    while ((c = getopt(argc, argv, "hlm:s:p:o:i:I:O:S:M:")) != EOF) {
        int parsedArgValue = charToLowerCase(c);
        switch(parsedArgValue) {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 's':
                minPartSize = stoi(optarg);
                break;
            case 'p':
                logFilename = optarg;
                break;
            case 'l':
                regMem = 1;
                break;
            case 'm':
                medianSize = stoi(optarg);
                break;
            case 'h':
                uso();
                exit(1);
            default:
                uso();
                exit(1);
        }
    }

    erroAssert(inputFile.size() > 0,
        "Analyser - nome do arquivo de entrada tem que ser definido");
    erroAssert(outputFile.size() > 0,
        "Analyser - nome do arquivo de saida tem que ser definido");
    erroAssert(medianSize > 0,
        "Analyser - tamanho da mediana do pivo nao deve ser nula");
}

int main(int argc, char ** argv) {
    parse_args(argc, argv);

    return 0;
}
