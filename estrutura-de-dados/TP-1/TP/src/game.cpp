#include "game.h"
#include "player.h"
#include "hand.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include "msgassert.h"

using namespace std;

Game::Game(string inFile, string outFile) {
    int nRounds = 0, iAmount = 0;

    Game::in = ifstream(inFile);
    Game::out = ofstream(outFile);

    Game::in >> nRounds >> iAmount;

    erroAssert(nRounds > 0, "Invalid number of rounds!");
    erroAssert(iAmount > 0, "Invalid initial amount!");

    Game::numberOfRounds = nRounds;
    Game::initialAmount = iAmount;
}

void deletePlayers(Player** p, int length) {
    for (int i = 0; i < length; i++) {
        delete p[i];
    }
    delete p;
}

Game::~Game() {
    Game::in.close();
    Game::out.close();
    deletePlayers(players,totalNumberOfPlayers);
    delete playersInRound;
}

Player** createPlayers(int n) {
    Player** players = new Player*[n];
    return players;
}

PlayerRef* createPlayersInRound(int n) {
    PlayerRef* players = new PlayerRef[n];
    return players;
}

void Game::getPlayerRoundInfo(string* name, int* bet) {
    string tmp;

    while (Game::in >> tmp) {
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

    Game::getPlayerRoundInfo(&name, &bet);

    if (Game::initialAmount < 0) {
        throw RoundException();
    }

    Player* p = new Player(name, Game::initialAmount);
    p->setHand(&(Game::in));

    p->setBet(bet);
    return p;
}

void Game::initPlayers() {
    erroAssert(Game::players != NULL, "Players not set!");
    for (int i = 0; i < Game::totalNumberOfPlayers; i++) {
        players[i] = createPlayer();
    }
}

void Game::mountPlayersInRound(bool isFirstRound) {
    Game::playersInRound = createPlayersInRound(Game::numberOfPlayersInRound);
    if (isFirstRound) {
        int i = 0;
        for (i = 0; i < Game::numberOfPlayersInRound; i ++) {
            Game::playersInRound[i].setRef(Game::players[i]);
        }
    } else {
        int i = 0, j = 0, idx = -1;
        bool found = false;
        for (i = 0; i < Game::numberOfPlayersInRound; i++) {
            found = false;
            idx = -1;
            j = 0;
            string playerName = "";
            int bet = 0;
            getPlayerRoundInfo(&playerName, &bet);
            while (!found && j < Game::totalNumberOfPlayers) {
                if (playerName == players[j]->getName()) {
                    found = true;
                    idx = j;
                }
                j++;
            }
            if (idx < 0) {
                throw RoundException();
            }
            Game::playersInRound[i].setRef(Game::players[idx]);
            Game::playersInRound[i].getRef()->setBet(bet);
            Game::playersInRound[i].getRef()->setHand(&(Game::in));
        }
    }
}

void Game::validateRound() {
    int i = 0;

    for (i = 0; i < Game::totalNumberOfPlayers; i++) {
        int totalToDiscount =
            Game::players[i]->getAmount() - Game::players[i]->getBet() - Game::anteValue;
        if (totalToDiscount < 0) {
            throw RoundException();
        }
    }
}

void Game::getAnteFromAllPlayers() {
    int i = 0;
    for (i = 0; i < Game::totalNumberOfPlayers; i++) {
        Game::players[i]->doAnte(Game::anteValue);
        Game::pot += Game::anteValue;
    }
}

void Game::getBetFromPlayersInRound() {
    int i = 0;
    for (i = 0; i < Game::numberOfPlayersInRound; i++) {
        Game::playersInRound[i].getRef()->doBet();
        Game::pot += Game::playersInRound[i].getRef()->getBet();
    }
}

void Game::resetRound() {
    Game::resetPot();
    delete playersInRound;

    int i = 0;
    for (i = 0; i < Game::totalNumberOfPlayers; i++) {
        Game::players[i]->resetBet();
    }
}

// Cria o setup inicial do round: apostas, pingo,
// jogadores da rodada
void Game::setRound(bool isFirstRound) {
    Game::resetRound();
    
    Game::numberOfPlayersInRound = 0;
    Game::anteValue = 0;
    
    Game::in >> numberOfPlayersInRound;
    if (numberOfPlayersInRound <= 0) {
        throw RoundException();
    }

    if (isFirstRound) {
        Game::totalNumberOfPlayers = Game::numberOfPlayersInRound;
    }

    Game::in >> anteValue;
    if (anteValue <= 0) {
        throw RoundException();
    }

    if (isFirstRound) {
        Game::players = createPlayers(Game::totalNumberOfPlayers);
        initPlayers();
    }

    Game::mountPlayersInRound(isFirstRound);

    Game::validateRound();
    
    Game::getAnteFromAllPlayers();
    Game::getBetFromPlayersInRound();
}

// Obtem o rank da mao de cada jogador
// da rodada
void Game::setPlayersRank() {
    int i = 0;
    for(i = 0; i < Game::numberOfPlayersInRound; i++) {
        Game::playersInRound[i].getRef()->getHand()->rankHand();
    }
}

void Game::sortPlayersByRank() {
    int i = 0, j = 0;

    // Bubble Sort
    // No entanto, esse sort coloca os maiores valores no inicio
    // Isso facilitara na remocao e para tratar empates
    for (i = 0; i < Game::numberOfPlayersInRound - 1; i++) {
        for (j = 0; j < Game::numberOfPlayersInRound - i - 1; j++) {
            if (*Game::playersInRound[j].getRef()->getHand() < Game::playersInRound[j + 1].getRef()->getHand()) {
                Player* tmp = Game::playersInRound[j].getRef();
                Game::playersInRound[j].setRef(Game::playersInRound[j+1].getRef());
                Game::playersInRound[j+1].setRef(tmp);
            }
        }
    }
}

// Checa, entre os jogadores da rodada, aqueles que tivere,
// o mesmo rank do maior Rank da rodada, que seria o jogador
// localizado na primeira posicao. Se for diferente do rank,
// elimina o jogador da rodada.
void Game::checkForDraws() {
    int i = 0, initialPlayersInRound = Game::numberOfPlayersInRound;
    Hand::Rank maxRank = Game::playersInRound[0].getRef()->getHand()->getRank();

    for (i = 1; i < initialPlayersInRound; i++) {
        Hand::Rank currRank = Game::playersInRound[i].getRef()->getHand()->getRank();
        if (currRank != maxRank) {
            Game::numberOfPlayersInRound--;
        }
    }
}

Hand::ComparationResult Game::handleComparation(int first, int second) {
    return playersInRound[first].getRef()->getHand()->compareWithSameRankHand(
        playersInRound[second].getRef()->getHand()
    );
}

void Game::removePlayerFromRound(int idx) {
    if (idx >= Game::numberOfPlayersInRound || idx < 0) return;
    for(int i = idx; i < Game::numberOfPlayersInRound - 1; i++)
        playersInRound[i].setRef(playersInRound[i+1].getRef());
    Game::numberOfPlayersInRound--;
}

// Decide o(s) vencedor(es) da rodada
void Game::handleDraws() {
    if (Game::numberOfPlayersInRound > 4 || Game::numberOfPlayersInRound < 0) {
        throw RoundException();
    }

    if (Game::numberOfPlayersInRound == 1) {
        return;
    }

    int lowerBound = 0;
    int higherBound = lowerBound + 1;
    int numberOfComparations = Game::numberOfPlayersInRound - 1;

    while (numberOfComparations > 0) {
        Hand::ComparationResult res = handleComparation(lowerBound, higherBound);
        if (res == Hand::ComparationResult::FirstWin) {
            removePlayerFromRound(higherBound);
        } else if (res == Hand::ComparationResult::SecondWin) {
            removePlayerFromRound(lowerBound);
        } else if (res == Hand::ComparationResult::Tie) {
            lowerBound = higherBound;
            higherBound = lowerBound + 1;
        }
        numberOfComparations--;
    }
}

void Game::handleRoundWinners() {
    int i = 0;
    string rank = Game::playersInRound[0].getRef()->getHand()->getRankName();
    int totalEarnedByEachWinner = Game::pot / Game::numberOfPlayersInRound;
    out << Game::numberOfPlayersInRound << " " << totalEarnedByEachWinner << " " << rank << endl;
    for (i = 0; i < Game::numberOfPlayersInRound; i++) {
        out << Game::playersInRound[i].getRef()->getName() << endl;
        Game::playersInRound[i].getRef()->increaseAmount(totalEarnedByEachWinner);
    }
}

void swap(Player *& a, Player *& b) {
    Player* c = a;
    a = b;
    b = c;
}

void Game::handleGameClassification() {
    out << "####" << endl;

    int i = 0, j = 0;

    // Bubble Sort
    for (i = 0; i < Game::totalNumberOfPlayers - 1; i++) {
        for (j = 0; j < Game::totalNumberOfPlayers - i - 1; j++) {
            if (Game::players[j]->getAmount() > Game::players[j+1]->getAmount()) {
                swap(Game::players[j], Game::players[j+1]);
            }
        }
    }

    for (i = Game::totalNumberOfPlayers - 1; i >= 0; i--) {
        out << Game::players[i]->getName() << " " << Game::players[i]->getAmount() << endl;
    }
}

// Lida com cada round da partida, declarando
// o(s) vencedor(es)
void Game::handleRound(bool isFirstRound) {
    try {
        Game::setRound(isFirstRound);
        Game::setPlayersRank();
        Game::sortPlayersByRank();
        Game::checkForDraws();
        Game::handleDraws();
        Game::handleRoundWinners();
    } catch (RoundException& err) {
        err.handle(&out);
        return;
    } catch (...) {
        abort();
    }
}

// Inicia o jogo
void Game::play() {
    // Fazer o setup do primeiro round
    // Esse setup e' diferente dos outros rounds,
    // pois cria o array com todos os jogadores
    Game::handleRound(true);

    for (int i = 1; i < Game::numberOfRounds; i++) {
        // Lidar com o restante dos rounds
        Game::handleRound();
    }
    handleGameClassification();
}
