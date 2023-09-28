#pragma once
#include <SFML/Graphics.hpp>
#include "Deck.h"

class Player {
public:
    Player();

    // Hand Management
    void drawInitialHand(Deck& mainDeck, int numCards);
    void drawCard(Deck& mainDeck);
    void addCardToHand(Card& card);
    Deck& getHand();
    int getHandSize();

    // Points Management
    int getPoints();
    void addToPoints(int value);

    // Display
    void handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);

private:
    Deck hand;
    int points;
};
