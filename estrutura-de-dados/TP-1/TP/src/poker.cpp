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

    if (regMem && strlen(logFilename) > 0) {
        iniciaMemLog(logFilename);
        ativaMemLog();
    } else {
        desativaMemLog();
    }

    Game* game = new Game("entrada.txt", "saida.txt");
    game->play();

    delete game;

    return regMem ? desativaMemLog() : 0;
}
