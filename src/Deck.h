#pragma once


#include "Card.h"
#include <vector>

class Deck {
public:
    Deck();
    void shuffle();
    Card dealCard();
    int size() const;

private:
    void initializeDeck();

    std::vector<Card> cards;
};

