#include "hand.h"
#include "card.h"
#include "stack.h"

#include <iostream>
#include "msgassert.h"

using namespace std;

Hand::~Hand() {
    delete pairsBundle;
    delete quadsBundle;
    delete triplesBundle;
    delete singlesBundle;
}

Hand::Hand() {
    rank = Hand::Rank::InvalidRank;
    singlesBundle = new Stack<Card::CardNumber>();
    pairsBundle = new Stack<Card::CardNumber>();
    triplesBundle = new Stack<Card::CardNumber>();
    quadsBundle = new Stack<Card::CardNumber>();
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        cards[i] = Card();
    }
}

void Hand::sortCards() {
    erroAssert(Hand::cards != NULL, "Hand cards are not setted!");

    // Bubble sort
    int i = 0, j = 0;
    for (i = 0; i < Hand::HAND_SIZE - 1; i++) {
        for (j = 0; j < Hand::HAND_SIZE - i - 1; j++) {
            if (cards[j] > cards[j + 1]) {
                Card tmp = cards[j];
                cards[j] = cards[j+1];
                cards[j+1] = tmp;
            }
        }
    }
}


void Hand::setCards(ifstream* in) {
    string tmp;
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        (*in) >> tmp;
        Hand::cards[i] = Card(tmp);
    }
    sortCards();
}

void Hand::print() {
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        if (i != Hand::HAND_SIZE - 1) {
            cout << Hand::cards[i].getCard() << " ";
        } else {
            cout << Hand::cards[i].getCard();
        }
    }
    cout << endl;
}

bool Hand::operator<(Hand* h) {
    return rank < h->getRank();
}

string Hand::getRankName() {
    bool isRankValid = Hand::rank != Hand::Rank::InvalidRank;
    avisoAssert(isRankValid, "Hand rank is not setted!");
    return RankNames[Hand::rank];
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
    for (i = 0; i < Hand::HAND_SIZE; i++) {
        // Como o valor das cartas comeca em 1,
        // e' necessaria a subtracao
        duplicates[Hand::cards[i].getValue() - FACTOR_TO_PARSE_CARD] += 1;
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
            Hand::singlesBundle->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Pair) {
            Hand::pairsBundle->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Triple) {
            Hand::triplesBundle->push((c));
            continue;
        } else if (reps == Hand::CardRepetition::Quad) {
            Hand::quadsBundle->push((c));
            continue;
        }
    }

    return 
        Hand::singlesBundle->size() + 
        Hand::pairsBundle->size() + 
        Hand::quadsBundle->size() + 
        Hand::triplesBundle->size();
}

// Ajustar mao quando o Às for a carta mais valiosa
void Hand::adjustHighAceStraightSort() {
    Card::CardNumber firstCard = Hand::cards[0].getValue();
    erroAssert(firstCard == Card::Ace, "This is not an high ace hand!");
    Card tmp = Hand::cards[0];
    Hand::cards[0] = Hand::cards[1];
    Hand::cards[1] = Hand::cards[2];
    Hand::cards[2] = Hand::cards[3];
    Hand::cards[3] = Hand::cards[4];
    Hand::cards[4] = tmp;
}

bool Hand::isHighAceStraight() {
    bool isHighAceStraight = false;

    if (Hand::cards[0].getValue()  == Card::Ace &&
        Hand::cards[1].getValue()  == Card::Ten &&
        Hand::cards[2].getValue() == Card::Jack && 
        Hand::cards[3].getValue()  == Card::Queen && 
        Hand::cards[4].getValue() == Card::King)
    {
        isHighAceStraight = true;
    }

    return isHighAceStraight;
}

bool Hand::isStraight() {
    erroAssert(!!Hand::cards, "Hand is empty!");
    bool isStraight = false;

    if (Hand::cards[1].getValue() == 
        Hand::cards[0].getValue() + 1 
            &&
        Hand::cards[2].getValue() == 
        Hand::cards[1].getValue() + 1 
            &&
        Hand::cards[3].getValue() == 
        Hand::cards[2].getValue() + 1 
            &&
        Hand::cards[4].getValue() == 
        Hand::cards[3].getValue() + 1) {
        isStraight = true;
    }
    /* NOTA:
    *  O rank straight pode ocorrer com a
    *  carta Às (Ace) sendo a mais valiosa
    */
    else if (Hand::isHighAceStraight()) {
        isStraight = true;
    }
      
    return isStraight;
}

bool Hand::isFlush() {
    erroAssert(!!Hand::cards, "Hand is empty!");
    Card::Suit firstSuit = Hand::cards[0].getSuit();
    for (int i = 1; i < Hand::HAND_SIZE; i++) {
        if (Hand::cards[i].getSuit() != firstSuit) {
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

    int combinationId = Hand::getNumberOfDuplicatesAndBuildBundles();

    erroAssert(combinationId != INVALID_COMBINATION, "Invalid combiantion -> 5 equal cards!");

    bool handIsFlush = Hand::isFlush();
    bool handIsStraight = Hand::isStraight();

    if (handIsStraight) {
        if (handIsFlush) {
            if (cards[0].getValue() == Card::CardNumber::Ace &&
                cards[Hand::HAND_SIZE - 1].getValue() == Card::CardNumber::King) {
                // Nesse caso, o As esta na primeira posicao. No entanto
                // ele e' a carta mais valiosa nessa combinacao.
                Hand::adjustHighAceStraightSort();
                Hand::setRank(Hand::Rank::RoyalStraightFlush);
                return;
            } else {
                Hand::setRank(Hand::Rank::StraightFlush);
                return;
            }
        } else {
            Hand::setRank(Hand::Rank::Straight);
            if (Hand::isHighAceStraight()) {
                Hand::adjustHighAceStraightSort();
            }
            return;
        }
    } else if (handIsFlush) {
        Hand::setRank(Hand::Rank::Flush);
        return;
    }

    switch(combinationId) {
        case FOUR_OF_KIND_OR_FULL_HOUSE_COMBINATION:
            if (Hand::hasQuadsBundle()) {
                Hand::setRank(Hand::Rank::FourOfAKind);
            } else {
                Hand::setRank(Hand::Rank::FullHouse);
            }
        break;

        case TWO_PAIRS_OR_THREE_OF_A_KIND_COMBINATION:
            if (Hand::hasTriplesBundle()) {
                Hand::setRank(Hand::Rank::ThreeOfAKind);
            } else {
                Hand::setRank(Hand::Rank::TwoPairs);
            }
        break;

        case ONE_PAIR_COMBINATION:
            Hand::setRank(Hand::Rank::OnePair);
            break;

        case OTHER_COMBINATION:
            Hand::setRank(Hand::Rank::HighCard);
        break;
    }
}

Hand::ComparationResult Hand::handleRepetitionsComparation(
    Stack<Card::CardNumber>* firstReps,
    Stack<Card::CardNumber>* secondReps
) {
    Hand::ComparationResult result = Hand::ComparationResult::Tie;

    Stack<Card::CardNumber>* firstRepsValues = new Stack<Card::CardNumber>();
    Stack<Card::CardNumber>* secondRepsValues = new Stack<Card::CardNumber>();

    while (!firstReps->empty() && !secondReps->empty()) {
        Card::CardNumber f = firstReps->pop();
        Card::CardNumber s = secondReps->pop();

        firstRepsValues->push(f);
        secondRepsValues->push(s);

        if (f > s) {
            result = Hand::ComparationResult::FirstWin;
            break;
        } else if (s > f) {
            result = Hand::ComparationResult::SecondWin;
            break;
        }
    }

    while (!firstRepsValues->empty()) {
        firstReps->push(firstRepsValues->pop());
    }

    while (!secondRepsValues->empty()) {
        secondReps->push(secondRepsValues->pop());
    }

    delete firstRepsValues;
    delete secondRepsValues;

    return result;
}

Hand::ComparationResult Hand::compareRepetitions(
    Hand* firstHand, 
    Hand* secondHand,
    Hand::CardRepetition repetition
) {
    Hand::ComparationResult result = Hand::ComparationResult::InvalidResult;

    switch (repetition) {
        case Hand::CardRepetition::Single: {
            result = Hand::handleRepetitionsComparation(
                firstHand->getSinglesBundle(),
                secondHand->getSinglesBundle()
            );
            break;
        }

        case Hand::CardRepetition::Pair: {
            result = Hand::handleRepetitionsComparation(
                firstHand->getPairsBundle(),
                secondHand->getPairsBundle()
            );
            break;
        }
        
        case Hand::CardRepetition::Triple: {
            result = Hand::handleRepetitionsComparation(
                firstHand->getTriplesBundle(),
                secondHand->getTriplesBundle()
            );
            break;
        }

        case Hand::CardRepetition::Quad: {
            result = Hand::handleRepetitionsComparation(
                firstHand->getQuadsBundle(),
                secondHand->getQuadsBundle()
            );
            break;
        }

        default:
            break;
    }

    return result;
}

Hand::ComparationResult Hand::compareHighCards(Hand* firstHand, Hand* secondHand) {
    // Utiliza a pilha de cartas unicas, ordenadas do maior para o menor, para
    // comparar as maos
    return Hand::compareRepetitions(firstHand, secondHand, Hand::CardRepetition::Single);
}

Hand::ComparationResult Hand::compareFourOfAKind(Hand* firstHand, Hand* secondHand) {
    // Compara as cartas que forma a Quadra. Se forem iguais, compara a carta
    // fora da combinacao
    Hand::ComparationResult result = Hand::compareRepetitions(
        firstHand,
        secondHand,
        Hand::CardRepetition::Quad
    );

    if (result == Hand::ComparationResult::Tie) {
        result = Hand::compareRepetitions(
            firstHand,
            secondHand,
            Hand::CardRepetition::Single
        );
    }

    return result;
}

Hand::ComparationResult Hand::compareFullHouse(Hand* firstHand, Hand* secondHand) {
    // Compara as cartas que formam a Tripla do FullHouse. Se forem iguais, 
    // compara as cartas quem formam a dupla.
    Hand::ComparationResult result = Hand::compareRepetitions(
        firstHand,
        secondHand,
        Hand::CardRepetition::Triple
    );

    if (result == Hand::ComparationResult::Tie) {
        result = Hand::compareRepetitions(
            firstHand,
            secondHand,
            Hand::CardRepetition::Pair
        );
    }

    return result;
}

Hand::ComparationResult Hand::compareThreeOfAKind(Hand* firstHand, Hand* secondHand) {
    // Compara as cartas que forma a Tripla. Se forem iguais,
    // compara as cartas fora da combinacao
    Hand::ComparationResult result = Hand::compareRepetitions(
        firstHand,
        secondHand,
        Hand::CardRepetition::Triple
    );

    if (result == Hand::ComparationResult::Tie) {
        result = Hand::compareRepetitions(
            firstHand,
            secondHand,
            Hand::CardRepetition::Single
        );
    }

    return result;
}

Hand::ComparationResult Hand::comparePairs(Hand* firstHand, Hand* secondHand) {
    // Compara as cartas que forma a Dupla Maior. Se forem iguais,
    // existem dois caminhos
    // - TwoPairs: compara o par menor, e se forem iguais, compara
    //   a carta fora da combinacao;
    // - OnePair: compara a carta fora da combinacao.
    Hand::ComparationResult result = Hand::compareRepetitions(
        firstHand,
        secondHand,
        Hand::CardRepetition::Pair
    );

    if (result == Hand::ComparationResult::Tie) {
        result = Hand::compareRepetitions(
            firstHand,
            secondHand,
            Hand::CardRepetition::Single
        );
    }

    return result;
}

Hand::ComparationResult Hand::compareWithSameRankHand(
    Hand* handToCompare
) {
    Hand::ComparationResult result = Hand::ComparationResult::InvalidResult;

    switch (Hand::rank) {
       case Hand::Rank::RoyalStraightFlush: {
            result = Hand::ComparationResult::Tie;
            break;
        }

        case Hand::Rank::StraightFlush: {
            result = Hand::compareHighCards(this, handToCompare);
            break;
        }

        case Hand::Rank::FourOfAKind: {
            result = Hand::compareFourOfAKind(this, handToCompare);
            break;
        }

        case Hand::Rank::FullHouse: {
            result = Hand::compareFullHouse(this, handToCompare);
            break;
        }

        case Hand::Rank::Flush: {
            result = Hand::compareHighCards(this, handToCompare);
            break;
        }

        case Hand::Rank::Straight: {
            result = Hand::compareHighCards(this, handToCompare);
            break;
        }

        case Hand::Rank::ThreeOfAKind: {
            result = Hand::compareThreeOfAKind(this, handToCompare);
            break;
        }

        case Hand::Rank::TwoPairs: {
            result = Hand::comparePairs(this, handToCompare);
            break;
        }

        case Hand::Rank::OnePair: {
            result = Hand::comparePairs(this, handToCompare);
            break;
        }

        case Hand::Rank::HighCard: {
            result = Hand::compareHighCards(this, handToCompare);
            break;
        }

        default: {
            break;
        }      
    }

    return result;
}
