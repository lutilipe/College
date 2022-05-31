#include "game.h"
#include "player.h"

#include <iostream>
#include "msgassert.h"

Game::Game(int nRounds, int iAmount) {
    erroAssert(nRounds > 0, "Invalid number of rounds!");
    erroAssert(iAmount > 0, "Invalid initial amount!");

    this->numberOfRounds = nRounds;
    this->initialAmount = iAmount;
}

Game::~Game() {
    delete[] this->players;
}

Player* createPlayers(int n) {
    Player* players = new Player[n];
    return players;
}

void getPlayerRoundInfo(string* name, int* bet) {
    string tmp;

    while (cin >> tmp) {
        try {
            (*bet) = stoi(tmp);
            break;
        } catch (...) {
            if (name->size()) {
                name += ' ';
            }
            (*name) += tmp;
        }
    }
}

Player Game::createPlayer() {
    int bet = 0;
    string name = "";

    getPlayerRoundInfo(&name, &bet);

    if (this->initialAmount - bet < 0) {
        this->isRoundValid = false;
    }

    Player p(name, this->initialAmount);
    p.setHand();
    p.setBet(bet);
    return p;
}

void Game::initPlayers(Player* players, int numberOfPlayers) {
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i] = createPlayer();
    }
}

void Game::setRound(bool isFirstRound) {
    int numberOfPlayers = 0,
        roundAnteValue = 0;
    
    cin >> numberOfPlayers;
    erroAssert(numberOfPlayers > 0,"Number of players is null!");
    this->numberOfPlayersInRound = numberOfPlayers;

    if (isFirstRound) {
        this->totalNumberOfPlayers = this->numberOfPlayersInRound;
    }

    cin >> roundAnteValue;
    erroAssert(roundAnteValue > 0,"Ante value is invalid!");
    this->anteValue = roundAnteValue;

    if (isFirstRound) {
        this->players = createPlayers(this->numberOfPlayersInRound);
    }

    this->isRoundValid = true;
}

void Game::handleRound() {
    setRound();
}

void Game::handleFirstRound() {
    setRound(true);
    initPlayers(this->players, this->totalNumberOfPlayers);
    for(int i = 0; i < this->totalNumberOfPlayers; i++) {
        players[i].printHand();
        cout << players[i].getAmount() << endl;
    }
}
