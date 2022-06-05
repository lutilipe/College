#include "msgassert.h"
#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Game* game = new Game("entrada.txt");

    game->play();

    delete game;

    return 0;
}
