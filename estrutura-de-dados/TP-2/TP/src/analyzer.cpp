#include <iostream>
#include <getopt.h>
#include <fstream>
#include <string.h>

#include "msgassert.h"
#include "wordVector.h"
#include "alphabeticOrder.h"
#include "word.h"
#include "utils.h"
#include "memlog.h"

using namespace std;

char logFilename[100];
string inputFile, outputFile;
int regMem = 0,
    minPartSize = 1,
    medianSize = 1;

const string ORDER_COMMAND = "#ORDEM";
const string TEXT_COMMAND = "#TEXTO";

void usage() {
    cout << "Analyzer\n" << endl;
    cout << "\t-h \t(comandos disponiveis)\n" << endl;
    cout << "\t-l \t(registrar acessos a memoria)\n" << endl;
    cout << "\t-p <arq>\t(arquivo de entrada da analise de memoria)\n" << endl;
    cout << "\t-i|I <arq>\t(arquivo de entrada)\n" << endl;
    cout << "\t-o|O <arq>\t(arquivo de saida)\n" << endl;
    cout << "\t-m|M \t(numero da mediana)\n" << endl;
    cout << "\t-s|S \t(tamanho minimo da particao para usar o QuickSort)\n" << endl;
}

// Seta o valor do parametro M e N como
// min(in, 1)
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

void addWordToVector(WordVector* v, Word& word) {
    int index = v->findIndex(word);
    if (index >= 0) {
        (*v)[index].increaseReps();
        return;
    }
    v->push(word);
}

// Verifica se o input e' #ORDEM ou #TEXTO (ordem nao importa)
// e cria uma nova ordem ou adiciona as palavras no vetor
void handleInput(ifstream* in, WordVector* v, string* newOrder) {
    string currCommand = "";
    string next = "";
    int currId = 0;

    while ((*in).peek() != EOF) {
        (*in) >> next;
        if (next[0] == '#') {
            currCommand = next;
            continue;
        }

        string tmp = stringToLowerCase(next);

        if (currCommand == ORDER_COMMAND) {
            (*newOrder) += tmp;
        } else {
            removeUnexpectedChars(&tmp);
            if (tmp != "") {
                Word w(tmp, currId);
                currId++;
                addWordToVector(v, w);
            }
        }
        next = "";
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
                strcpy(logFilename, optarg);
                break;
            case 'l':
                regMem = 1;
                break;
            case 'm':
                medianSize = getInputNumber(optarg);
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
        "Analyser - nome do arquivo de entrada precisa ser definido");
    erroAssert(outputFile.size() > 0,
        "Analyser - nome do arquivo de saida precisa ser definido");
}

int main(int argc, char ** argv) {
    parse_args(argc, argv);

    bool logEnabled = strlen(logFilename) > 0;

    if (logEnabled) {
        iniciaMemLog(logFilename);
    }

    if (regMem) {
        ativaMemLog();
    } else {
        desativaMemLog();
    }

    ifstream in = ifstream(inputFile);
    erroAssert(!in.fail(), "File not found");

    ofstream out = ofstream(outputFile);

    defineFaseMemLog(0);
    WordVector* v = new WordVector(medianSize, minPartSize);
    string newOrder = "";
    handleInput(&in, v, &newOrder);

    AlphabeticOrder order(newOrder);

    v->parseWords(order);
    v->sort();
    v->print(&out);

    delete v;

    in.close();
    out.close();

    return logEnabled ? finalizaMemLog() : 0;
}
