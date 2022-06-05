#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <fstream>

using namespace std;

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;
        int pot = 0;
        ifstream in;
        ofstream out;

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
        Game(string inFile, string outFile);
        ~Game();

        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void increasePot(int n) { pot += n; };
        int getPot() { return pot; };
        void resetPot() { pot = 0; };

        void play();
};

class RoundException {
    public:
        RoundException() {}

        void handle(ofstream* out) {
            string s = "0 0 I";
            *out << s << endl;
        }
};

#endif
