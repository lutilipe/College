#include <iostream>
#include <getopt.h>
#include "msgassert.h"
#include "wordVector.h"
#include "alphabeticOrder.h"
#include "utils.h"

using namespace std;

string logFilename,
    inputFile,
    outputFile;
int regMem = 0,
    minPartSize = 1,
    medianSize = 1;

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

int parseNullish(int in) {
    return in ? in : 1;
}

int getInputNumber(char* optarg) {
    try {
        return parseNullish(stoi(optarg));
    } catch (...) {
        return 1;
    }
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
                minPartSize = getInputNumber(optarg);
                break;
            case 'p':
                logFilename = optarg;
                break;
            case 'l':
                regMem = 1;
                break;
            case 'm':
                medianSize = getInputNumber(optarg);
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
        "Analyser - nome do arquivo de entrada precisa ser definido");
    erroAssert(outputFile.size() > 0,
        "Analyser - nome do arquivo de saida precisa ser definido");
}

int main(int argc, char ** argv) {
    parse_args(argc, argv);

    string newOrder = "ZYWXVUTSRQPONMLKJIHGFEDCBA";

    AlphabeticOrder order(newOrder);

    WordVector<int>* v = new WordVector<int>(medianSize, minPartSize);
    v->push(2);
    v->push(4);
    v->push(1);
    v->push(5);
    v->push(3);

    v->sort();

    delete v;

    return 0;
}
