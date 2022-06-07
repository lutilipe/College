#include "hand.h"
#include "card.h"
#include "stack.h"
#include "game.h"

#include <iostream>
#include "msgassert.h"
#include "memlog.h"

using namespace std;

Hand::~Hand() {
    delete pairsBundle;
    delete quadsBundle;
    delete triplesBundle;
    delete singlesBundle;
}

Hand::Hand(int i) {
    id = i;
    rank = Hand::Rank::InvalidRank;
    singlesBundle = new Stack<Card::Number>(Hand::id);
    pairsBundle = new Stack<Card::Number>(Hand::id);
    triplesBundle = new Stack<Card::Number>(Hand::id);
    quadsBundle = new Stack<Card::Number>(Hand::id);
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        cards[i] = Card();
        ESCREVEMEMLOG((long int)(&(cards[i])),sizeof(Card),Hand::id);
    }
}

void Hand::setRank(Hand::Rank r) {
    ESCREVEMEMLOG((long int)(&(rank)),sizeof(Hand::Rank),Hand::id);
    rank = r; 
};

Hand::Rank Hand::getRank() {
    LEMEMLOG((long int)(&(rank)),sizeof(Hand::Rank),Hand::id);
    return rank; 
};

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

void Hand::resetHand() {
    Hand::singlesBundle->clean();
    Hand::pairsBundle->clean();
    Hand::triplesBundle->clean();
    Hand::quadsBundle->clean();
}

void Hand::setCards(ifstream* in) {
    string tmp;
    Hand::resetHand();
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        (*in) >> tmp;
        Hand::cards[i] = Card(tmp, Hand::id);
        ESCREVEMEMLOG((long int)(&(cards[i])),sizeof(Card),Hand::id);
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
    return Hand::getRank() < h->getRank();
}

string Hand::getRankName() {
    bool isRankValid = Hand::getRank() != Hand::Rank::InvalidRank;
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
    Card::Number maxNumber = Card::Ace;
    const int FACTOR_TO_PARSE_CARD = 1;

    int duplicates[maxNumber];

    // Inicializa duplicates com 0;
    for (i = 0; i < maxNumber; i++) {
        duplicates[i] = 0;
    }

    // Soma 1 em cada posicacao do vetor referente
    // ao valor da carta analisada
    for (i = 0; i < Hand::HAND_SIZE; i++) {
        // Como o valor das cartas comeca em 1,
        // e' necessaria a subtracao
        int index = Hand::cards[i].getValue() - FACTOR_TO_PARSE_CARD ;
        duplicates[index] += 1;
    }

    // Para cada valor do vetor "duplicate",
    // e' checada a repeticao para "buildar"
    // as pilhas com cada repeticao
    for (i = 0; i < maxNumber; i++) {
        int reps = duplicates[i];
        erroAssert(!(reps > 4), "Error during build repetitions!");
        if (reps == 0) continue;
        Card::Number c = (Card::Number) (i + FACTOR_TO_PARSE_CARD);
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

// Ajustar mao quando o Às for a carta menos valiosa
// Isso ocorre em sequencias Straigth do As ao 5
void Hand::adjustLowerAceStraight() {
    Card::Number lastCard = Hand::cards[Hand::HAND_SIZE - 1].getValue();
    if (!(lastCard == Card::Ace)) {
        return;
    }
    Card tmp = Hand::cards[0];
    Hand::cards[0] = Hand::cards[4];
    Hand::cards[1] = tmp;
    Hand::cards[2] = Hand::cards[1];
    Hand::cards[3] = Hand::cards[2];
    Hand::cards[4] = Hand::cards[3];
}

bool Hand::isLowerAceStraight() {
    bool isLowerAceStraight = false;

    if (Hand::cards[0].getValue()  == Card::Two &&
        Hand::cards[1].getValue() == Card::Three && 
        Hand::cards[2].getValue()  == Card::Four && 
        Hand::cards[3].getValue() == Card::Five &&
        Hand::cards[4].getValue()  == Card::Ace)
    {
        isLowerAceStraight = true;
    }

    return isLowerAceStraight;
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
        Hand::cards[3].getValue() + 1) 
    {
        isStraight = true;
    }
    /* NOTA:
    *  O rank straight pode ocorrer com a
    *  carta Às (Ace) sendo a menos valiosa.
    *  Ex: As, 2, 3, 4, 5
    */
    else if (Hand::isLowerAceStraight()) {
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
    enum Combinations {
        // Essa combinacao ocorre se sao passadas 5
        // cartas iguais, tornando a mao invalida
        INVALID_COMBINATION = 1,

        FOUR_OF_KIND_OR_FULL_HOUSE_COMBINATION = 2,
        TWO_PAIRS_OR_THREE_OF_A_KIND_COMBINATION = 3,
        ONE_PAIR_COMBINATION = 4,
        OTHER_COMBINATION = 5,
    };

    int combinationId = Hand::getNumberOfDuplicatesAndBuildBundles();

    if (combinationId == Combinations::INVALID_COMBINATION) {
        throw RoundException();
    }

    bool handIsFlush = Hand::isFlush();
    bool handIsStraight = Hand::isStraight();

    if (handIsStraight) {
        if (handIsFlush) {
            if (cards[0].getValue() == Card::Number::Ten &&
                cards[Hand::HAND_SIZE - 1].getValue() == Card::Number::Ace) {
                Hand::setRank(Hand::Rank::RoyalStraightFlush);
                return;
            } else {
                Hand::setRank(Hand::Rank::StraightFlush);
                if (Hand::isLowerAceStraight()) {
                    Hand::adjustLowerAceStraight();
                }
                return;
            }
        } else {
            Hand::setRank(Hand::Rank::Straight);
            if (Hand::isLowerAceStraight()) {
                Hand::adjustLowerAceStraight();
            }
            return;
        }
    } else if (handIsFlush) {
        Hand::setRank(Hand::Rank::Flush);
        return;
    }

    switch(combinationId) {
        case Combinations::FOUR_OF_KIND_OR_FULL_HOUSE_COMBINATION:
            if (Hand::hasQuadsBundle()) {
                Hand::setRank(Hand::Rank::FourOfAKind);
            } else {
                Hand::setRank(Hand::Rank::FullHouse);
            }
        break;

        case Combinations::TWO_PAIRS_OR_THREE_OF_A_KIND_COMBINATION:
            if (Hand::hasTriplesBundle()) {
                Hand::setRank(Hand::Rank::ThreeOfAKind);
            } else {
                Hand::setRank(Hand::Rank::TwoPairs);
            }
        break;

        case Combinations::ONE_PAIR_COMBINATION:
            Hand::setRank(Hand::Rank::OnePair);
            break;

        case Combinations::OTHER_COMBINATION:
            Hand::setRank(Hand::Rank::HighCard);
        break;
    }
}

// Lida com as cartas repetidas nas maos de dois jogadoeres.
Hand::ComparationResult Hand::handleRepetitionsComparation(
    Stack<Card::Number>* firstReps,
    Stack<Card::Number>* secondReps
) {
    Hand::ComparationResult result = Hand::ComparationResult::Tie;

    Stack<Card::Number>* firstRepsValues = new Stack<Card::Number>(Hand::id);
    Stack<Card::Number>* secondRepsValues = new Stack<Card::Number>(Hand::id);

    // Compara cada carta de cada jogador. As cartas estao ordenadas
    // na pilha do maior para o menor
    while (!firstReps->empty() && !secondReps->empty()) {
        Card::Number f = firstReps->pop();
        Card::Number s = secondReps->pop();

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

    // Repoe na pilha os valores removidos
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
