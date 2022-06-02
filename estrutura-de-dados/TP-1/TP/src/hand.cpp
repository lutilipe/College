#include "hand.h"
#include "card.h"

#include <iostream>
#include "msgassert.h"
#include "utils.h"

using namespace std;

Hand::~Hand() {
    delete pairs;
    delete quads;
    delete triples;
    delete singles;
}

void Hand::sortCards() {
    erroAssert(this->cards != NULL, "Hand cards not setted!");
    sort(this->cards, HAND_SIZE);
}

void Hand::setCards(ifstream* in) {
    string tmp;
    for (int i = 0; i < HAND_SIZE; i++) {
        (*in) >> tmp;
        this->cards[i] = Card(tmp);
    }

    sortCards();
}

void Hand::print() {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i != HAND_SIZE - 1) {
            cout << this->cards[i].getCard() << " ";
        } else {
            cout << this->cards[i].getCard();
        }
    }
    cout << endl;
}

int Hand::getNumberOfDuplicatesAndBuild() {
    int i = 0;
    Card::CardNumber maxCardNumber = Card::KING;
    const int FACTOR_TO_PARSE_CARD = 1;

    int duplicates[maxCardNumber];

    // Inicializa duplicates com 0;
    for (i = 0; i < maxCardNumber; i++) {
        duplicates[i] = 0;
    }

    // Soma 1 em cada posicacao do vetor referente
    // ao valor da carta analisada
    for (i = 0; i < HAND_SIZE; i++) {
        // Como o valor das cartas comeca em 1,
        // e' necessaria a subtracao
        duplicates[this->cards[i].getValue() - FACTOR_TO_PARSE_CARD] += 1;
    }

    int numberOfDuplications = 0;
    
    // Para cada valor do vetor "duplicate",
    // e' checada a repeticao para "buildar"
    // as pilhas com cada repeticao
    for (i = 0; i < maxCardNumber; i++) {
        int reps = duplicates[i];
        erroAssert(!(reps > 4), "Error during build repetitions!");
        if (reps == 0) continue;
        Card::CardNumber c = (Card::CardNumber) (i + FACTOR_TO_PARSE_CARD);
        if (reps == Hand::CardRepetition::SINGLE) {
            this->singles->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::PAIR) {
            this->pairs->push((c));
            numberOfDuplications++;
            continue;
        } else if (reps == Hand::CardRepetition::TRIPLE) {
            this->triples->push((c));
            numberOfDuplications++;
            continue;
        } else if (reps == Hand::CardRepetition::QUAD) {
            this->quads->push((c));
            numberOfDuplications++;
            continue;
        }
    }

    return numberOfDuplications;
}

// Ajustar mao quando o Às for a carta mais valiosa
void Hand::adjustAceStraightSort() {
    Card::CardNumber firstCard = this->cards[0].getValue();
    erroAssert(firstCard == Card::ACE, "This is not an high ace hand!");
    Card tmp = this->cards[0];
    this->cards[0] = this->cards[1];
    this->cards[1] = this->cards[2];
    this->cards[2] = this->cards[3];
    this->cards[3] = this->cards[4];
    this->cards[4] = tmp;
}

bool Hand::isHighAceStraight() {
    bool isHighAceStraight = false;

    if (this->cards[0].getValue()  == Card::ACE &&
        this->cards[1].getValue()  == Card::TEN &&
        this->cards[2].getValue() == Card::JACK && 
        this->cards[3].getValue()  == Card::QUEEN && 
        this->cards[4].getValue() == Card::KING)
    {
        isHighAceStraight = true;
    }

    return isHighAceStraight;
}

bool Hand::isStraight() {
    erroAssert(!!this->cards, "Hand is empty!");
    bool isStraight = false;

    if (this->cards[0].getValue() == 
        this->cards[1].getValue() + 1 
            &&
        this->cards[1].getValue() == 
        this->cards[2].getValue() + 1 
            &&
        this->cards[2].getValue() == 
        this->cards[3].getValue() + 1 
            &&
        this->cards[3].getValue() == 
        this->cards[4].getValue() + 1) {
        isStraight = true;
    }
    /* NOTA:
    *  O rank straight pode ocorrer com a
    *  carta Às (Ace) sendo a mais valiosa
    */
    else if (this->isHighAceStraight()) {
        isStraight = true;
    }
      
    return isStraight;
}

bool Hand::isFlush() {
    erroAssert(!!this->cards, "Hand is empty!");
    Card::Suit firstSuit = this->cards[0].getSuit();
    for (int i = 1; i < HAND_SIZE; i++) {
        if (this->cards[i].getSuit() != firstSuit) {
            return false;
        }
    }
    return true;
}

void Hand::rankHand() {
    int i = getNumberOfDuplicatesAndBuild();
    cout << i << endl;
}