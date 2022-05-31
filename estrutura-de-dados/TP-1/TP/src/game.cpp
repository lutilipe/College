#include "game.h"
#include "player.h"

#include <iostream>
#include <fstream>
#include "msgassert.h"

using namespace std;

Game::Game(string inFile) {
    int nRounds = 0, iAmount = 0;

    this->in = ifstream(inFile);

    this->in >> nRounds >> iAmount;

    erroAssert(nRounds > 0, "Invalid number of rounds!");
    erroAssert(iAmount > 0, "Invalid initial amount!");

    this->numberOfRounds = nRounds;
    this->initialAmount = iAmount;
}

Game::~Game() {
    this->in.close();
    delete[] this->players;
}

Player* createPlayers(int n) {
    Player* players = new Player[n];
    return players;
}

void Game::getPlayerRoundInfo(string* name, int* bet) {
    string tmp;

    while (this->in >> tmp) {
        try {
            (*bet) = stoi(tmp);
            break;
        } catch (...) {
            if (name->size()) {
                (*name) += ' ';
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
    p.setHand(&in);
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
    
    this->in >> numberOfPlayers;
    erroAssert(numberOfPlayers > 0,"Number of players is null!");
    this->numberOfPlayersInRound = numberOfPlayers;

    if (isFirstRound) {
        this->totalNumberOfPlayers = this->numberOfPlayersInRound;
    }

    this->in >> roundAnteValue;
    erroAssert(roundAnteValue > 0,"Ante value is invalid!");
    this->anteValue = roundAnteValue;

    if (isFirstRound) {
        this->players = createPlayers(this->numberOfPlayersInRound);
    }

    this->isRoundValid = true;
}

void Game::handleRound() {
    //setRound();
}

void Game::handleFirstRound() {
    setRound(true);
    initPlayers(this->players, this->totalNumberOfPlayers);
    for(int i = 0; i < this->totalNumberOfPlayers; i++) {
        cout << players[i].getName() << endl;
        players[i].printHand();
        cout << players[i].getAmount() << endl;
    }
}

void Game::play() {
    handleFirstRound();
    for (int i = 0; i < this->numberOfRounds; i++) {
        handleRound();
    }
}