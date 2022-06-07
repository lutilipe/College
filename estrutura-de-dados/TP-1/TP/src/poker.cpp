#include "msgassert.h"
#include "game.h"
#include "memlog.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>

using namespace std;

bool regMem = false;
char logFilename[100];

void parseArgs(int argc,char ** argv) {
    int c;
    while ((c = getopt(argc, argv, "lp:")) != EOF) {
        switch(c) {
            case 'l':
                regMem = true;
                break;
            
            case 'p':
                strcpy(logFilename, optarg);
                break;
        }
    }
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

    Game* game = new Game("entrada.txt", "saida.txt");
    game->play();

    delete game;

    return logEnabled ? desativaMemLog() : 0;
}
