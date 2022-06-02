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
            SINGLE = 1,
            PAIR,
            TRIPLE,
            QUAD
        };

        static const int HAND_SIZE = 5;

        Hand() {};
        ~Hand();

        void setRank(Hand::Rank r) { rank = r; };
        Hand::Rank getRank() { return rank; };
        void rankHand();

        void setCards(ifstream* in);
        void sortCards();
        void print();

        Stack<Card::CardNumber>* getSingles() { return pairs; };
        Stack<Card::CardNumber>* getPairs() { return quads; };
        Stack<Card::CardNumber>* getTriples() { return singles; };
        Stack<Card::CardNumber>* getQuads() { return triples; };

        void setSingles(Stack<Card::CardNumber>* c) { pairs = c; };
        void setPairs(Stack<Card::CardNumber>* c) { quads = c; };
        void setTriples(Stack<Card::CardNumber>* c) { singles = c; };
        void setQuads(Stack<Card::CardNumber>* c) { triples = c; };

        bool hasSingles() { return pairs != NULL && !pairs->empty(); };
        bool hasPairs() { return quads != NULL && !quads->empty(); };
        bool hasTriples() { return singles != NULL && !singles->empty(); };
        bool hasQuads() { return triples != NULL && !triples->empty(); };

    private:
        Hand::Rank rank;
        Card cards[HAND_SIZE];

        Stack<Card::CardNumber>* pairs = new Stack<Card::CardNumber>();;
        Stack<Card::CardNumber>* quads = new Stack<Card::CardNumber>();;
        Stack<Card::CardNumber>* singles = new Stack<Card::CardNumber>();;
        Stack<Card::CardNumber>* triples = new Stack<Card::CardNumber>();;

        bool isRoyalStraighFlush();
        bool isStraighFlush();
        bool isFlush();
        bool isStraight();
        bool isHighAceStraight();
        void adjustAceStraightSort();

        int getNumberOfDuplicatesAndBuild();
};

#endif