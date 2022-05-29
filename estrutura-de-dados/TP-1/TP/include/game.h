#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;

        Player* players;

        void setRound(bool isFirstRound = false);
    public:
        Game(int nRounds, int iAmount);
        ~Game();
        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void handleFirstRound();
        void handleRound();
};

#endif