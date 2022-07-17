#include "msgassert.h"
#include "memlog.h"
#include "email.h"
#include "email-box.h"
#include "email-server.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>

using namespace std;

bool regMem = false;
char logFilename[100];
string inputFile, outputFile;

void usage() {
    cout << "Analyzer\n" << endl;
    cout << "\t-h \t(comandos disponiveis)\n" << endl;
    cout << "\t-l \t(registrar acessos a memoria)\n" << endl;
    cout << "\t-p <arq>\t(arquivo de entrada da analise de memoria)\n" << endl;
    cout << "\t-i <arq>\t(arquivo de entrada)\n" << endl;
    cout << "\t-o <arq>\t(arquivo de saida)\n" << endl;
}

void parseArgs(int argc,char ** argv) {
    int c;

    while ((c = getopt(argc, argv, "hli:o:")) != EOF) {
        switch(c) {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'p':
                strcpy(logFilename, optarg);
                break;
            case 'l':
                regMem = 1;
                break;
            case 'h':
                usage();
                exit(1);
            default:
                usage();
                exit(1);
        }
    }

    erroAssert(inputFile.size() > 0,
        "Email - nome do arquivo de entrada precisa ser definido");
    erroAssert(outputFile.size() > 0,
        "Email - nome do arquivo de saida precisa ser definido");
}

int main(int argc, char ** argv) {
    parseArgs(argc, argv);

    bool logEnabled = strlen(logFilename) > 0;

    if (logEnabled) {
        iniciaMemLog(logFilename);
    }

    if (regMem) {
        ativaMemLog();
    } else {
        desativaMemLog();
    }

    return logEnabled ? finalizaMemLog() : 0;
}
