#ifndef HAND_RANK_H
#define HAND_RANK_H

#include <iostream>
#include <fstream>
#include "card.h"
#include "stack.h"

using namespace std;

class Hand {
    public:
        enum Rank {
            InvalidRank,
            HighCard,
            OnePair,
            TwoPairs,
            ThreeOfAKind,
            Straight,
            Flush,
            FullHouse,
            FourOfAKind,
            StraightFlush,
            RoyalStraightFlush,
        };

        enum CardRepetition {
            Single = 1,
            Pair,
            Triple,
            Quad
        };

        enum ComparationResult {
            InvalidResult,
            FirstWin,
            SecondWin,
            Tie,
        }; 

        static const int HAND_SIZE = 5;

        Hand(int id);
        ~Hand();

        void setRank(Hand::Rank r);
        Hand::Rank getRank();
        string getRankName();
        void rankHand();

        void setCards(ifstream* in);
        void sortCards();
        void print();

        Stack<Card::Number>* getSinglesBundle() { return singlesBundle; };
        Stack<Card::Number>* getPairsBundle() { return pairsBundle; };
        Stack<Card::Number>* getTriplesBundle() { return triplesBundle; };
        Stack<Card::Number>* getQuadsBundle() { return quadsBundle; };

        void setSinglesBundle(Stack<Card::Number>* c) { singlesBundle = c; };
        void setPairsBundle(Stack<Card::Number>* c) { pairsBundle = c; };
        void setTriplesBundle(Stack<Card::Number>* c) { triplesBundle = c; };
        void setQuadsBundle(Stack<Card::Number>* c) { quadsBundle = c; };

        bool hasSinglesBundle() { return singlesBundle != NULL && !singlesBundle->empty(); };
        bool hasPairsBundle() { return pairsBundle != NULL && !pairsBundle->empty(); };
        bool hasTriplesBundle() { return triplesBundle != NULL && !triplesBundle->empty(); };
        bool hasQuadsBundle() { return quadsBundle != NULL && !quadsBundle->empty(); };

        Hand::ComparationResult compareWithSameRankHand(Hand* handToCompare);

        bool operator < (Hand* h);
    private:
        int id = -1;
        Hand::Rank rank;
        Card cards[Hand::HAND_SIZE];

        // Utilizados para comparar maos com mesmo rank
        Stack<Card::Number>* singlesBundle;
        Stack<Card::Number>* pairsBundle;
        Stack<Card::Number>* triplesBundle;
        Stack<Card::Number>* quadsBundle;

        bool isRoyalStraighFlush();
        bool isStraighFlush();
        bool isFlush();
        bool isStraight();
        bool isLowerAceStraight();
        void adjustLowerAceStraight();

        int getNumberOfDuplicatesAndBuildBundles();

        void resetHand();

        Hand::ComparationResult compareHighCards(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareFourOfAKind(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareFullHouse(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareThreeOfAKind(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult comparePairs(Hand* firstHand, Hand* secondHand);

        Hand::ComparationResult compareRepetitions(
            Hand* firstHand, 
            Hand* secondHand,
            Hand::CardRepetition repetition
        );

        Hand::ComparationResult handleRepetitionsComparation(
            Stack<Card::Number>* firstReps,
            Stack<Card::Number>* secondReps
        );

        const string RankNames[11] = {
            "I",
            "HC",
            "OP",
            "TP",
            "TK",
            "S",
            "F",
            "FH",
            "FK",
            "SF",
            "RSF"
        };
};

#endif