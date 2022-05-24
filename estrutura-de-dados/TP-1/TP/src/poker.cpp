#include "msgassert.h"
#include "game.h"

#include <iostream>

using namespace std;

int main() {
    int numberOfRounds = 0;
    int initialAmount = 0;

    cin >> numberOfRounds >> initialAmount;

    erroAssert(numberOfRounds > 0, "Invalid number of rounds!");
    erroAssert(initialAmount > 0, "Invalid initial amount!");

    Game* game = new Game(numberOfRounds, initialAmount);

    game->handleFirstRound();

    delete game;

    return 0;
}