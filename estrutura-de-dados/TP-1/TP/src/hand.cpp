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

string Hand::getRankName() {
    bool isRankValid = this->rank != Hand::Rank::InvalidRank;
    avisoAssert(isRankValid, "Hand rank is not setted!");
    return RankNames[this->rank];
};

/* Criar bundles (stacks) com cada repeticao
* e gera um int representando possiveis
* ranks para as cartas, baseado na duplicidade
* delas. 
*/
int Hand::getNumberOfDuplicatesAndBuildBundles() {
    int i = 0;
    Card::CardNumber maxCardNumber = Card::King;
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

    // Para cada valor do vetor "duplicate",
    // e' checada a repeticao para "buildar"
    // as pilhas com cada repeticao
    for (i = 0; i < maxCardNumber; i++) {
        int reps = duplicates[i];
        erroAssert(!(reps > 4), "Error during build repetitions!");
        if (reps == 0) continue;
        Card::CardNumber c = (Card::CardNumber) (i + FACTOR_TO_PARSE_CARD);
        if (reps == Hand::CardRepetition::Single) {
            this->singles->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Pair) {
            this->pairs->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Triple) {
            this->triples->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Quad) {
            this->quads->push((c));
            continue;
        }
    }

    return 
        this->singles->size() + 
        this->pairs->size() + 
        this->quads->size() + 
        this->triples->size();
}

// Ajustar mao quando o Às for a carta mais valiosa
void Hand::adjustHighAceStraightSort() {
    Card::CardNumber firstCard = this->cards[0].getValue();
    erroAssert(firstCard == Card::Ace, "This is not an high ace hand!");
    Card tmp = this->cards[0];
    this->cards[0] = this->cards[1];
    this->cards[1] = this->cards[2];
    this->cards[2] = this->cards[3];
    this->cards[3] = this->cards[4];
    this->cards[4] = tmp;
}

bool Hand::isHighAceStraight() {
    bool isHighAceStraight = false;

    if (this->cards[0].getValue()  == Card::Ace &&
        this->cards[1].getValue()  == Card::Ten &&
        this->cards[2].getValue() == Card::Jack && 
        this->cards[3].getValue()  == Card::Queen && 
        this->cards[4].getValue() == Card::King)
    {
        isHighAceStraight = true;
    }

    return isHighAceStraight;
}

bool Hand::isStraight() {
    erroAssert(!!this->cards, "Hand is empty!");
    bool isStraight = false;

    if (this->cards[1].getValue() == 
        this->cards[0].getValue() + 1 
            &&
        this->cards[2].getValue() == 
        this->cards[1].getValue() + 1 
            &&
        this->cards[3].getValue() == 
        this->cards[2].getValue() + 1 
            &&
        this->cards[4].getValue() == 
        this->cards[3].getValue() + 1) {
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
    // Essa combinacao ocorre se sao passadas 5
    // cartas iguais, tornando a mao invalida
    const int INVALID_COMBINATION = 1;

    const int FOUR_OF_KIND_OR_FULL_HOUSE_COMBINATION = 2;
    const int TWO_PAIRS_OR_THREE_OF_A_KIND_COMBINATION = 3;
    const int ONE_PAIR_COMBINATION = 4;
    const int OTHER_COMBINATION = 5;

    int combinationId = getNumberOfDuplicatesAndBuildBundles();

    erroAssert(combinationId != INVALID_COMBINATION, "Invalid combiantion -> 5 equal cards!");

    bool handIsFlush = isFlush();
    bool handIsStraight = isStraight();

    if (handIsStraight) {
        if (handIsFlush) {
            if (cards[0].getValue() == Card::CardNumber::Ace &&
                cards[HAND_SIZE - 1].getValue() == Card::CardNumber::King) {
                // Nesse caso, o As esta na primeira posicao. No entanto
                // ele e' a carta mais valiosa nessa combinacao.
                adjustHighAceStraightSort();
                setRank(Hand::Rank::RoyalStraightFlush);
                return;
            } else {
                setRank(Hand::Rank::StraightFlush);
                return;
            }
        } else {
            setRank(Hand::Rank::Straight);
            if (isHighAceStraight()) {
                adjustHighAceStraightSort();
            }
            return;
        }
    } else if (handIsFlush) {
        setRank(Hand::Rank::Flush);
        return;
    }

    switch(combinationId) {
        case FOUR_OF_KIND_OR_FULL_HOUSE_COMBINATION:
            if (hasQuads()) {
                setRank(Hand::Rank::FourOfAKind);
            } else {
                setRank(Hand::Rank::FullHouse);
            }
        break;

        case TWO_PAIRS_OR_THREE_OF_A_KIND_COMBINATION:
            if (hasTriples()) {
                setRank(Hand::Rank::ThreeOfAKind);
            } else {
                setRank(Hand::Rank::TwoPairs);
            }
        break;

        case ONE_PAIR_COMBINATION:
            setRank(Hand::Rank::OnePair);
            break;

        case OTHER_COMBINATION:
            setRank(Hand::Rank::HighCard);
        break;
    }
}