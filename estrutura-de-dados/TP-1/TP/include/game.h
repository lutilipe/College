#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <fstream>

using namespace std;

class RoundException {
    public:
        RoundException() {}

        void handle() {
            // Todo: Write to file
            cout << 0 << " " << 0 << " " << "I" << endl;
        }
};

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;
        int pot = 0;
        ifstream in;

        Player** players;
        PlayerRef* playersInRound;

        void setRound(bool isFirstRound = false);
        void initPlayers();
        void getPlayerRoundInfo(string* name, int* bet);
        Player* createPlayer();

        void handleRound(bool isFirstRound = false);

        void setPlayersRank();
        void sortPlayersByRank();
        void checkForDraws();
        void handleDraws();
        void handleRoundWinners();

        void removePlayerFromRound(int idx);

        Hand::ComparationResult handleComparation(int first, int second);

        void mountPlayersInRound(bool isFirstRound = false);
        void getAnteFromAllPlayers();
        void getBetFromPlayersInRound();

        void handleGameWinners();
    public:
        Game(string inFile);
        ~Game();

        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void increasePot(int n) { pot += n; };
        int getPot() { return pot; };
        void resetPot() { pot = 0; };

        void play();
};

#endif