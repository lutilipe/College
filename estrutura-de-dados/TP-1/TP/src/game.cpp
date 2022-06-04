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

void deletePlayers(Player** p, int length) {
    for (int i = 0; i < length; i++) {
        delete p[i];
    }
    delete p;
}

Game::~Game() {
    this->in.close();
    deletePlayers(players,totalNumberOfPlayers);
    deletePlayers(playersInRound,totalNumberOfPlayers);
}

Player** createPlayers(int n) {
    Player** players = new Player*[n];
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

Player* Game::createPlayer() {
    int bet = 0;
    string name = "";

    getPlayerRoundInfo(&name, &bet);

    if (this->initialAmount - bet < 0) {
        this->isRoundValid = false;
    }

    Player* p = new Player(name, this->initialAmount);
    p->getHand()->setCards(&in);

    p->setBet(bet);
    return p;
}

void Game::initPlayers() {
    erroAssert(this->players != NULL, "Players not set!");
    for (int i = 0; i < this->totalNumberOfPlayers; i++) {
        players[i] = createPlayer();
    }
}

void Game::mountPlayersInRound(bool isFirstRound) {
    if (!isFirstRound) {
        deletePlayers(this->playersInRound, this->totalNumberOfPlayers);
    }

    this->playersInRound = createPlayers(this->numberOfPlayersInRound);
    if (isFirstRound) {
        int i = 0;
        for (i = 0; i < this->numberOfPlayersInRound; i ++) {
            this->playersInRound[i] = new Player(*this->players[i]);
        }
    } else {
        // TODO
        return;
    }
}

void Game::setRound(bool isFirstRound) {
    this->isRoundValid = true;

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
        this->players = createPlayers(this->totalNumberOfPlayers);
        initPlayers();
        mountPlayersInRound(true);
    }
}

void swap(Player *& a, Player *& b) {
    Player* c = a;
    a = b;
    b = c;
}

void Game::sortPlayersByRank() {
    int i = 0, j = 0;

    // Bubble Sort
    for (i = 0; i < this->numberOfPlayersInRound - 1; i++) {
        for (j = 0; j < this->numberOfPlayersInRound - i - 1; j++) {
            if (*(this->playersInRound[j]->getHand()) > this->playersInRound[j + 1]->getHand()) {
                swap(this->playersInRound[j], this->playersInRound[j+1]);
            }
        }
    }
}

void Game::checkForDraw() {

}

void Game::handleDraw() {

}

void Game::handleRound(bool isFirstRound) {
    setRound(isFirstRound);
    for(int i = 0; i < this->numberOfPlayersInRound; i++) {
        playersInRound[i]->getHand()->rankHand();
    }
    sortPlayersByRank();
    for(int i = 0; i < this->numberOfPlayersInRound; i++) {
        cout << playersInRound[i]->getName() << endl;
        playersInRound[i]->getHand()->print();
        cout << playersInRound[i]->getHand()->getRankName() << endl << endl;
    }
}

void Game::play() {
    handleRound(true);
    for (int i = 1; i < this->numberOfRounds; i++) {
        handleRound();
    }
}