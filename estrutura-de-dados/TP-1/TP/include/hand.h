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

        static const int HAND_SIZE = 5;

        Hand() {};
        ~Hand();

        void setRank(Hand::Rank r) { rank = r; };
        Hand::Rank getRank() { return rank; };
        string getRankName();
        void rankHand();

        void setCards(ifstream* in);
        void sortCards();
        void print();

        Stack<Card::CardNumber>* getSingles() { return singles; };
        Stack<Card::CardNumber>* getPairs() { return pairs; };
        Stack<Card::CardNumber>* getTriples() { return triples; };
        Stack<Card::CardNumber>* getQuads() { return pairs; };

        void setSingles(Stack<Card::CardNumber>* c) { singles = c; };
        void setPairs(Stack<Card::CardNumber>* c) { pairs = c; };
        void setTriples(Stack<Card::CardNumber>* c) { triples = c; };
        void setQuads(Stack<Card::CardNumber>* c) { quads = c; };

        bool hasSingles() { return pairs != NULL && !singles->empty(); };
        bool hasPairs() { return quads != NULL && !pairs->empty(); };
        bool hasTriples() { return singles != NULL && !triples->empty(); };
        bool hasQuads() { return triples != NULL && !quads->empty(); };

    private:
        Hand::Rank rank = Hand::Rank::InvalidRank;
        Card cards[HAND_SIZE];

        Stack<Card::CardNumber>* singles = new Stack<Card::CardNumber>();
        Stack<Card::CardNumber>* pairs = new Stack<Card::CardNumber>();
        Stack<Card::CardNumber>* triples = new Stack<Card::CardNumber>();
        Stack<Card::CardNumber>* quads = new Stack<Card::CardNumber>();

        bool isRoyalStraighFlush();
        bool isStraighFlush();
        bool isFlush();
        bool isStraight();
        bool isHighAceStraight();
        void adjustHighAceStraightSort();

        int getNumberOfDuplicatesAndBuildBundles();

        const string RankNames[11] = {
            "Invalid",
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